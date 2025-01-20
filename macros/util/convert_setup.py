import os
import sys

def convert_macro(input_file):
    try:
        # Generate the output file name
        output_file = input_file.replace(".C", "_conv.C")
        
        with open(input_file, 'r') as infile:
            lines = infile.readlines()
        
        with open(output_file, 'w') as outfile:
            # Write the new header
            outfile.write('#include "Riostream.h"\n\n')
            outfile.write('void setup(TFRSParameter* frs,\n')
            outfile.write('        TMWParameter* mw,\n')
            outfile.write('        TTPCParameter* tpc,\n')
            outfile.write('        TMUSICParameter* music,\n')
            outfile.write('        TLABRParameter* labr,\n')
            outfile.write('        TSCIParameter* sci,\n')
            outfile.write('        TIDParameter* id,\n')
            outfile.write('        TSIParameter* si,\n')
            outfile.write('        TMRTOFMSParameter* mrtof,\n')
            outfile.write('        TRangeParameter* range)\n')
            outfile.write('{\n')
            
            # Flag to start copying lines after finding "frs->rho0"
            found_rho_line = False

            for line in lines:
                # Skip the line containing `an->`
                if 'an->' in line:
                    continue
                
                # Start copying after "frs->rho0"
                if "frs->rho0" in line:
                    found_rho_line = True
                
                if found_rho_line:
                    outfile.write(line)
        
        print(f"Converted macro saved to {output_file}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    # Check if a file name is provided
    if len(sys.argv) != 2:
        print("Usage: python convert_macro.py <input_macro.C>")
    else:
        input_macro = sys.argv[1]
        if not input_macro.endswith(".C"):
            print("Error: Input file must have a .C extension.")
        elif not os.path.exists(input_macro):
            print(f"Error: File {input_macro} not found.")
        else:
            convert_macro(input_macro)
