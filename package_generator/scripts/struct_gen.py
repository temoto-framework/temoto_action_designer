import json
import jinja2
import argparse
import os

# Define the JSON-to-C++ type mapping
TYPE_MAPPING = {
    "number": "double",
    "numbers": "std::vector<double>",
    "bool": "bool",
    "bools": "std::vector<bool>",
    "string": "std::string",
    "strings": "std::vector<std::string>"
}

def generate_cpp_structs(json_data, struct_name="input_parameters_t"):
    """
    Recursively generate C++ structs from a JSON dictionary.
    """
    structs = []

    def process_object(obj, name):
        fields = []
        nested_structs = []

        for key, value in obj.items():

            if value.get("pvf_type") is None:
                # Handle nested objects recursively
                nested_struct_name = key + "_t"
                nested_structs.extend(process_object(value, nested_struct_name))
                fields.append((nested_struct_name, key))
            else:
                # Map JSON types to C++ types
                cpp_type = TYPE_MAPPING.get(value["pvf_type"])
                fields.append((cpp_type, key))

        # Add the current struct to the list
        structs.append({"name": name, "fields": fields})
        return nested_structs

    process_object(json_data, struct_name)
    return structs

def generate_struct_init(json_data):
    """
    Recursively generate C++ initialization code for the given JSON data.
    """
    lines = []

    def process_object(obj, name=""):
        for key, value in obj.items():
            field_access = ""

            if name:
                field_access = f"{name}.{key}"
            else:
                field_access = key

            if value.get("pvf_type") is None:
                process_object(value, field_access)
            else:
                cpp_type = TYPE_MAPPING.get(value["pvf_type"])
                param_key = field_access.replace(".", "::")
                lines.append((field_access, {"cpp_type": cpp_type, "param_key": param_key}))
            
    process_object(json_data)
    return lines

def main():

    # Create the argument parser
    parser = argparse.ArgumentParser(description="Action package generator.")

    # Add arguments
    parser.add_argument("--umrf-json", type=str, help="Path to UMRF JSON.")
    parser.add_argument("--templates", type=str, help="Path to jinja templates.")
    parser.add_argument("--output", type=str, help="Path to generated output files.")

    gen_path = "generated"

    # Parse the arguments
    args = parser.parse_args()

    # Load the JSON
    json_data = None

    with open(args.umrf_json) as f:
        json_data = json.load(f)

    #
    # Load jinja templates
    #
    templateLoader = jinja2.FileSystemLoader(searchpath=args.templates)
    templateEnv = jinja2.Environment(loader=templateLoader)

    template_structs = templateEnv.get_template('param_structs.jinja')
    template_init    = templateEnv.get_template('param_init.jinja')

    #
    # Render input parameter C++ structs
    #
    input_structs = generate_cpp_structs(json_data["input_parameters"])
    render_cpp_input_param_structs = template_structs.render(structs=input_structs)
    print(render_cpp_input_param_structs)

    with open(os.path.join(gen_path, "include", "input_parameters.hpp"), "w") as f:
        f.write(render_cpp_input_param_structs)

    #
    # Render output parameter C++ structs
    #
    output_structs = generate_cpp_structs(json_data["output_parameters"])
    render_cpp_output_param_structs = template_structs.render(structs=output_structs)
    print(render_cpp_output_param_structs)

    with open(os.path.join(gen_path, "include", "output_parameters.hpp"), "w") as f:
        f.write(render_cpp_output_param_structs)

    #
    # Render the input/output param C++ struct initialization
    #
    lines = generate_struct_init(json_data["input_parameters"])
    cpp_output_init = template_init.render(lines=lines, interface_direction="Input")
    print(cpp_output_init)

if __name__ == "__main__":
    main()


