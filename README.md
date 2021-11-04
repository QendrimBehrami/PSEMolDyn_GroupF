MolSim Group F
===
<h2>Info</h2>
git repository link:https://github.com/iheathrow/MolSim2021-Group-F

Commit ID:

Group ID and members: MolSim2021-Group-F, Qendrim Behrami, Ilia Khitrov, Yujie Zhang <br>
Builds compiled with g++ compiler.

<h2>Build</h2>
In the main directory run: <br><br>
mkdir -p build <br>
cd build <br>
cmake ../ <br>
make <br>

<h2>Usage</h2>

Inside the build directoy, run: <br><br>
`./MolSim -i [filename] -d [delta_t] -e [end_time]`

Example: <br><br>
`./MolSim -i ../eingabe-sonne.txt -d 0.01 -e 100`
