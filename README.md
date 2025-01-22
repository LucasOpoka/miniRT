<table align="center">
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/patterns/patterns3.png" width="150" height="150"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/mccree.png" width="150" height="150"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/bonus_bump_refr.png" width="150" height="150"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/bonus_objects2.png" width="150" height="150"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/texture_bump_refraction.png" width="150" height="150"></th>
  </tr>
  <tr><th colspan="6"><a href="https://github.com/LucasOpoka/miniRT?tab=readme-ov-file#gallery">Full Gallery</a></th></tr>
</table>

# Quickstart guide for Linux (Debian Like)

Install dependencies
```bash
sudo apt update
sudo apt install git cmake make build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
```

Clone MLX42 repository
```bash
git clone https://github.com/codam-coding-college/MLX42.git
```

Build MLX42
```bash
cd MLX42
cmake -B build
cmake --build build -j4
cd ..
```

Clone miniRT repository
```bash
git clone https://github.com/LucasOpoka/miniRT.git
```

Build miniRT Mandatory version - for scenes_mandatory
```bash
cd miniRT
make
```
Build miniRT Bonus version - for secenes_bonus
```bash
cd miniRT
make bonus
```

Test run
```bash
./miniRT scenes_mandatory/8_shadows.rt
```

# Quickstart guide for Linux (Debian Like) with Docker

Build Docker
```
docker build -t minirt - << EOF
FROM ubuntu
ENV DISPLAY=:0
RUN apt update && apt install -qqy x11-apps git cmake make build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
RUN git clone https://github.com/codam-coding-college/MLX42.git
RUN cd MLX42 && cmake -B build && cmake --build build -j4 && cd ..
RUN git clone https://github.com/LucasOpoka/miniRT.git
WORKDIR /miniRT
RUN make bonus
CMD ["./miniRT", "scenes_bonus/texture_bump_refraction.rt"]
EOF
```

Run Docker
```
XSOCK=/tmp/.X11-unix
XAUTH=/tmp/.docker.xauth
xauth nlist :0 | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -
docker run -ti -v $XSOCK:$XSOCK -v $XAUTH:$XAUTH -e XAUTHORITY=$XAUTH minirt
```

# Gallery

<table align="center">
  <tr><th colspan="6">Textures - Bump Textures - Refraction</th></tr>
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/bonus_texture.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/bonus_bump_white.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/refraction.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/bonus_bump_refr.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/texture_bump_refraction.png" width="100" height="100"></th>
  </tr>
  <tr>
    <td align="center">texture</td>
    <td align="center">bump</td>
    <td align="center">refraction</td>
    <td align="center">bump + refraction</td>
    <td align="center">texture + bump + refraction</td>
  </tr>
</table>

<table align="center">
  <tr><th colspan="6">Triangles</th></tr>
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/bonus_triangles.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/mccree.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/mccree_arches.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/mccree_checkers.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/mccree_rings.png" width="100" height="100"></th>

  </tr>
</table>

<table align="center">
  <tr><th colspan="6">Intro Scenes</th></tr>
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/intro/basic1.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/intro/basic2.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/intro/basic3.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/intro/basic4.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/intro/basic5.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/intro/basic6.png" width="100" height="100"></th>
  </tr>
</table>


<table align="center">
  <tr><th colspan="4">Patterns scenes</th></tr>
  <tr><th colspan="4"><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/patterns/patterns1.png" height="100"></th></tr>
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/patterns/patterns2.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/patterns/patterns3.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/patterns/patterns4.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/patterns/patterns5.png" width="100" height="100"></th>
  </tr>
</table>


<table align="center">
  <tr><th colspan="5">Misc scenes</th></tr>
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/bonus_objects1.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/bonus_objects2.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/box.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/compass.png" width="100" height="100"></th>
  </tr>
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/cone_madness.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/ominous_triangle.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/glass_pill.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/advanced/light.png" width="100" height="100"></th>
  </tr>
</table>


<table align="center">
  <tr><th colspan="5">Solar system scenes</th></tr>
  <tr><th colspan="5"><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/solar%20system.png" height="100"></th></tr>
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/sun.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/mercury.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/venus.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/earth.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/mars.png" width="100" height="100"></th>
    
  </tr>
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/jupiter.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/saturn.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/uranus.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/neptune.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/solar_system/pluto.png" width="100" height="100"></th>
    
  </tr>
</table>


<table align="center">
  <tr><th colspan="4">Misshaps along the way</th></tr>
  <tr>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/misshaps/misshap1.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/misshaps/misshap2.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/misshaps/misshap3.png" width="100" height="100"></th>
    <th><img src="https://github.com/LucasOpoka/miniRT/blob/main/assets/misshaps/misshap4.png" width="100" height="100"></th>
  </tr>
</table>
