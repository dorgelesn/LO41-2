# LO41 Project

Simulation of a chain factory in C language, using threads and shared memory

## Usage

./bin/LO41 [-debug] <produits> <types> <tables>\n\
\
    -<produits>: fichier contenant les produits a usiner.\
    -<types>: fichier contenant les types de produits.\
    -<tables>: fichier contenant les tables d'usinage.
```bash
./bin/LO41 produits.txt types.txt tables.txt

./bin/LO41 -debug p.txt ty.txt ta.txt
```

## Why ?

The purpose of this project is to show that i understood the subjects that we saw in class.

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

There is no additional dependencies for this project, it only uses standards libraries

## Licence

Copyright (C) 2016 Nicolas Ballet

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the
Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
Boston, MA  02110-1301, USA.
