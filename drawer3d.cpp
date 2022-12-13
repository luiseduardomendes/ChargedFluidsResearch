
void Display::show_3d(){
    al_clear_to_color(al_map_rgb(0x00, 0x11, 0x20));
    this->draw_box_3d();
    this->draw_particles_3d();
    al_flip_display();
}

void Display::draw_particles_3d(){
    auto temp = this->particles;
    _sort(temp);
    
    for (auto p : temp){

        double cte = (p->pos.z*fov/(box->sup.z-box->inf.z) + 1*fov);

        al_draw_filled_circle(
            p->pos.x*zoom*CTE_CONV*cte + w/2, 
            p->pos.y*zoom*CTE_CONV*cte + h/2,
            p->radius*zoom*CTE_CONV*cte, 
            p->color
        );

        al_draw_circle(
            p->pos.x*zoom*CTE_CONV*cte + w/2, 
            p->pos.y*zoom*CTE_CONV*cte + h/2,
            p->radius*zoom*CTE_CONV*cte, 
            al_map_rgb(0,0,0), 0.2*p->radius*zoom*CTE_CONV*cte
        );
    }    
}

void Display::draw_box_3d(){
    double cte_h = 1.5*fov;
    double cte_l = 0.5/fov;
    al_draw_rectangle(
        box->inf.x * zoom*CTE_CONV*cte_h + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_h + h/2, 
        box->sup.x * zoom*CTE_CONV*cte_h + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_h + h/2, 
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_rectangle(
        box->inf.x * zoom*CTE_CONV*cte_l + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_l + h/2, 
        box->sup.x * zoom*CTE_CONV*cte_l + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_l + h/2, 
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_line(
        box->inf.x * zoom*CTE_CONV*cte_l + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_l + h/2, 
        box->inf.x * zoom*CTE_CONV*cte_h + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_h + h/2,
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_line(
        box->sup.x * zoom*CTE_CONV*cte_l + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_l + h/2, 
        box->sup.x * zoom*CTE_CONV*cte_h + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_h + h/2,
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_line(
        box->inf.x * zoom*CTE_CONV*cte_l + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_l + h/2, 
        box->inf.x * zoom*CTE_CONV*cte_h + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_h + h/2,
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_line(
        box->sup.x * zoom*CTE_CONV*cte_l + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_l + h/2, 
        box->sup.x * zoom*CTE_CONV*cte_h + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_h + h/2,
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );

}

void Display::draw_grid_3d(){
    double i = 0.5*fov;
    double inc = 1.0/10.0;
    while (i <= 1.5/fov){
        al_draw_rectangle(
            box->inf.x * zoom*CTE_CONV*i + w/2, 
            box->inf.y * zoom*CTE_CONV*i + h/2, 
            box->sup.x * zoom*CTE_CONV*i + w/2, 
            box->sup.y * zoom*CTE_CONV*i + h/2, 
            al_map_rgb(0x80,0x80,0x80),
            1
        );
        i += inc;
    }
    i = 0.5*fov;
    while (i <= 1.5/fov){
        double j = -(box->sup.x - box->inf.x)/2;
        double inc_j = (box->sup.x - box->inf.x)/10;
        while (j <= (box->sup.x - box->inf.x)/2){
            al_draw_line(
                j * zoom*CTE_CONV*i*fov + w/2, 
                box->inf.y * zoom*CTE_CONV*i*fov + h/2, 
                j * zoom*CTE_CONV*i*fov + w/2, 
                box->sup.y * zoom*CTE_CONV*i*fov + h/2, 
                al_map_rgb(0x80,0x80,0x80),
                1
            );
            j += inc_j;
        }
        double k = -(box->sup.y - box->inf.y)/2;
        double inc_k = (box->sup.y - box->inf.y)/10;
        while (k <= (box->sup.x - box->inf.x)/2){
            al_draw_line(
                box->inf.x * zoom*CTE_CONV*i*fov + w/2, 
                k * zoom*CTE_CONV*i*fov + h/2, 
                box->sup.x * zoom*CTE_CONV*i*fov + w/2, 
                k * zoom*CTE_CONV*i*fov + h/2, 
                al_map_rgb(0x80,0x80,0x80),
                1
            );
            k += inc_k;
        }
        i += inc;
    }
}


