## Domain file

The CCOLab use the VTK FIELD file format to save the perfusion domain
informations.

The file structure is given below.

```
# vtk DataFile Version 3.0
<Short title (it must have less than 256 characters).>
ASCII
FIELD <field name> 4
dimension 1 1 int
<point dimension>

<area | volume> 1 1 double
<value in m² | m³)>

seeds <point dimension> <n points> double
p0x p0y <p0z>
p1x p1y <p1z>
…
p(n-1)x p(n-1)y <p(n-1)z>

points <point dimension> <m points> double
p0x p0y <p0z>
p1x p1y <p1z>
…
p(m-1)x p(m-1)y <p(m-1)z>
```

If the domain dimension is 2 the point z-coordinate is not mandatory.

See [`/data/circle/default-circle.vtk`](/data/circle/default-circle.vtk) or 
[`/data/sphere/default-sphere.vtk`](/data/sphere/default-sphere.vtk) as 
an domain file example.

## Tree file

The CCOLab use the VTK DATASET POLYDATA file format to save the tree
informations.

The file structure is given below.

```
# vtk DataFile Version 3.0
<Short title (it must have less than 256 characters).>
ASCII
DATASET POLYDATA
POINTS <n points> double
p0x p0y p0z
p1x p1y p1z
…
p(n-1)x p(n-1)y p(n-1)z

LINES <m lines> <3*m>
2 i0 j0
2 i1 j1
2 i2 j2
…
2 i(m-1) j(m-1)

CELL_DATA <m lines>
SCALARS radius double
LOOKUP_TABLE default
r0
r1
r2
…
r(m-1)
```

Use 0 as the point z-coordinate if its dimension is 2.