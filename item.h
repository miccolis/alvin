struct Item {
   uint8_t image;
   uint8_t dim[2];
   MFRC522::Uid uid;
};

// It's unfortunate to have the dimentions separte from the image definitions but
// I think they're too hard to refer too in the see of binary data that is images.h
void loadItems(Item v[]) {
    // blackCar
    v[0].image = 0;
    v[0].dim[0] = 84;
    v[0].dim[1] = 36;
    // TODO define uid

    // datsun
    v[1].image = 1;
    v[1].dim[0] = 84;
    v[1].dim[1] = 31;
    // TODO define uid

    // redCar
    v[2].image = 2;
    v[2].dim[0] = 84;
    v[2].dim[1] = 29;
    // TODO define uid

    // snowplow
    v[3].image = 3;
    v[3].dim[0] = 84;
    v[3].dim[1] = 36;
    // TODO define uid
}

