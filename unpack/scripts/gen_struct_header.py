import subprocess as sb



systems = ["FATIMA", "Germanium"]

ucesb_exec = "S452"



for system in systems:
    sb.run(ucesb_exec+"/"+ucesb_exec)
    