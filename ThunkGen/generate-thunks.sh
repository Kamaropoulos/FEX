#!/bin/bash

# libGL - OpenGL + GLX

## guest side
python3 libGL-thunks.py thunks > ../ThunkLibs/libGL/libGL_Thunks.inl
python3 libGL-thunks.py symtab > ../ThunkLibs/libGL/libGL_Syms.inl #needed for glXGetProc

## host side
python3 libGL-thunks.py thunkmap     > ../ThunkLibs/libGL/libGL_Thunkmap.inl
python3 libGL-thunks.py initializers > ../ThunkLibs/libGL/libGL_Forwards.inl
python3 libGL-thunks.py forwards    >> ../ThunkLibs/libGL/libGL_Forwards.inl



# libX11

## guest side
python3 libX11-thunks.py thunks > ../ThunkLibs/libX11/libX11_Thunks.inl

## host side
python3 libX11-thunks.py thunkmap     > ../ThunkLibs/libX11/libX11_Thunkmap.inl
python3 libX11-thunks.py initializers > ../ThunkLibs/libX11/libX11_Forwards.inl
python3 libX11-thunks.py forwards    >> ../ThunkLibs/libX11/libX11_Forwards.inl



# libEGL

## guest side
python3 libEGL-thunks.py thunks > ../ThunkLibs/libEGL/libEGL_Thunks.inl

## host side
python3 libEGL-thunks.py thunkmap     > ../ThunkLibs/libEGL/libEGL_Thunkmap.inl
python3 libEGL-thunks.py initializers > ../ThunkLibs/libEGL/libEGL_Forwards.inl
python3 libEGL-thunks.py forwards    >> ../ThunkLibs/libEGL/libEGL_Forwards.inl


# libXfixes

## guest side
python3 libXfixes-thunks.py thunks > ../ThunkLibs/libXfixes/libXfixes_Thunks.inl

## host side
python3 libXfixes-thunks.py thunkmap     > ../ThunkLibs/libXfixes/libXfixes_Thunkmap.inl
python3 libXfixes-thunks.py initializers > ../ThunkLibs/libXfixes/libXfixes_Forwards.inl
python3 libXfixes-thunks.py forwards    >> ../ThunkLibs/libXfixes/libXfixes_Forwards.inl

# libXrender

## guest side
python3 libXrender-thunks.py thunks > ../ThunkLibs/libXrender/libXrender_Thunks.inl

## host side
python3 libXrender-thunks.py thunkmap     > ../ThunkLibs/libXrender/libXrender_Thunkmap.inl
python3 libXrender-thunks.py initializers > ../ThunkLibs/libXrender/libXrender_Forwards.inl
python3 libXrender-thunks.py forwards    >> ../ThunkLibs/libXrender/libXrender_Forwards.inl


# libXext

## guest side
python3 libXext-thunks.py thunks > ../ThunkLibs/libXext/libXext_Thunks.inl

## host side
python3 libXext-thunks.py thunkmap     > ../ThunkLibs/libXext/libXext_Thunkmap.inl
python3 libXext-thunks.py initializers > ../ThunkLibs/libXext/libXext_Forwards.inl
python3 libXext-thunks.py forwards    >> ../ThunkLibs/libXext/libXext_Forwards.inl

# libSDL2

## guest side
python3 libSDL2-thunks.py thunks > ../ThunkLibs/libSDL2/libSDL2_Thunks.inl

## host side
python3 libSDL2-thunks.py thunkmap     > ../ThunkLibs/libSDL2/libSDL2_Thunkmap.inl
python3 libSDL2-thunks.py initializers > ../ThunkLibs/libSDL2/libSDL2_Forwards.inl
python3 libSDL2-thunks.py forwards    >> ../ThunkLibs/libSDL2/libSDL2_Forwards.inl