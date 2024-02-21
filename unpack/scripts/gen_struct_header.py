import subprocess as sb


#should create the correct struct files, add systems to systems list and run. 

#add the systems you want here: bplast,fatima,etc
systems = ["germanium"]

ucesb_exec = "onlyGerm"


for system in systems:
    sb.run(["../exps/" + ucesb_exec + "/" + ucesb_exec, f"--ntuple=UNPACK:{system},STRUCT_HH,id=h101_{system},NOTRIGEVENTNO,ext_h101_{system}.h"])
    
    """filename = f"ext_h101_{system}.h"

    with open(filename, 'r') as file:
        content = file.read()

    # Identify the indices of the first two and last two occurrences of "h101"
    modified_content = content.replace("h101", f"h101_{system.upper()}")

    with open(filename, 'w') as file:
        file.write(modified_content)
    """
    
    sb.run(["mv",f"ext_h101_{system}.h",f"../../c4source/{system}/"])
    
    

