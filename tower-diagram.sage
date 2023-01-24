pol = Graphics(); 

file_name = input("Enter the file name to take vertex data: ").rstrip('\n')

if not file_name.endswith(".txt"):
  file_name += ".txt"

output_name = input("Specify an output name {options: .png(default) .svg or .pdf}: ").rstrip('\n')

if not (output_name.endswith(".png") or output_name.endswith(".svg") or output_name.endswith(".pdf")):
  output_name += ".png"

file_p = open(file_name, "r")

file_p_input = file_p.readline()

vertex_list = []

while(file_p_input != ""):
  file_p_input.rstrip('\n')
  vertex_list.append([int(i) for i in file_p_input.split()])
  file_p_input = file_p.readline()

file_p.close()

for [a,b] in vertex_list:
  pol += polygon([(a,b),(a+1,b),(a+1,b+1),(a,b+1)], fill=False, color='black')

pol.axes_color("blue")
pol.save(output_name ,xmin=-1, xmax=round(pol.get_minmax_data()["xmax"]*1.3), ymin=-1, ymax=round(pol.get_minmax_data()["ymax"]*1.3))


