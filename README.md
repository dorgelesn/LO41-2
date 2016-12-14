# LO41 Project

Simulation of a chain factory in C language, using threads and shared memory

## Usage

```bash
./bin/LO41 [-debug] <produits> <types> <tables>

    -<produits>: fichier contenant les produits a usiner.
    -<types>: fichier contenant les types de produits.
    -<tables>: fichier contenant les tables d\'usinage.

./bin/LO41 produits.txt types.txt tables.txt

./bin/LO41 -debug p.txt ty.txt ta.txt
```

## Why ?

The purpose of this project is to show that i understood the subjects that we saw in class of LO41 at UTBM in Belfort,
in France.

## Installation

Clone the project
```bash
git clone https://github.com/gnikwo/LO41
```

and install gcc if it's not done yet
```bash
apt install gcc
```

finaly, compile the project
```bash
make
```

### Dependencies 

There is no additional dependencies for this project, it only uses standard libraries

## Licence

This project is under MIT licence.
Further informations in the 'licence' file at the root of this project.
