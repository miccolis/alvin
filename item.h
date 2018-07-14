struct Item {
   //uint8_t image;
   uint16_t dim[2];
   MFRC522::Uid uid;
};

void setItemUid(Item *v, uint8_t size, uint8_t sak, uint8_t bytes[]) {
    v->uid.size = size;
    v->uid.sak = sak;
    for (uint8_t i = 0; i < size; i++) {
        v->uid.uidByte[i] = bytes[i];
    }
}

bool compareUid(MFRC522::Uid *a, MFRC522::Uid *b) {
    if (a->size != b->size) return false;
    if (b->sak != a->sak) return false;
    for (uint8_t i = 0; i < a->size; i++){
        if (a->uidByte[i] != b->uidByte[i]) return false;
    }
    return true;
}

// Returns `len + 1` if item is not found
uint8_t findItemByUid(Item list[], uint8_t len, MFRC522::Uid *uid) {
    for (uint8_t i = 0; i < len; i++) {
        if (compareUid(&(list[i].uid), uid)) {
            return i;
        }
    }
    return len + 1;
}

// It's unfortunate to have the dimensions separate from the image definitions but
// I think they're too hard to refer too in the see of binary data that is images.h
void loadItems(Item v[]) {
    // blackCar
    //v[0].image = 0;
    v[0].dim[0] = 88;
    v[0].dim[1] = 36;
    const uint8_t bytes0[4] = {0x97,0x8C,0x0F,0xF2};
    setItemUid(&v[0], 4, 8, bytes0);

    // datsun
    //v[1].image = 1;
    v[1].dim[0] = 88;
    v[1].dim[1] = 32;
    const uint8_t bytes1[4] = {0x57,0x86,0x0F,0xF2};
    setItemUid(&v[1], 4, 8, bytes1);

    // redCar
    //v[2].image = 2;
    v[2].dim[0] = 88;
    v[2].dim[1] = 32;
    const uint8_t bytes2[4] = {0xF7,0x85,0x0F,0xF2};
    setItemUid(&v[2], 4, 8, bytes2);

    // snowplow
    //v[3].image = 3;
    v[3].dim[0] = 88;
    v[3].dim[1] = 36;
    const uint8_t bytes3[4] = {0x17,0xC7,0x0D,0xF2};
    setItemUid(&v[3], 4, 8, bytes3);
}

