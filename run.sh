gcc main.c -O2 allegro_interface.c box.c common.c display.c particles.c vector.c simulation.c $(pkg-config --libs allegro-5 allegro_font-5  allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_dialog-5 --cflags) -lm -o build/out2
./build/out2 saida.txt
