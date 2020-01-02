#include "resourcemanager.h"

ResourceManager::ResourceManager(QWidget* parent, ObjectManager* gom)
{
    parent_ = parent;
    gom_ = gom;

    //Asetetaan resursseille alkuarvot
    modifyResource("money", 200);
    modifyResource("concrete", 40);
    modifyResource("mead", 25);
    modifyResource("credits", 0);
}

void ResourceManager::modifyResource(QString res, int amount) {
    // Modifies players resources according to func call

    if (resources_.contains(res)) {
        resources_[res] += amount;
    } else {
        resources_[res] = amount;
    }
}

int ResourceManager::getResource(QString res) {
    // Returns the ammount of given resource

    if (resources_.contains(res)) {
        return resources_[res];
    } else {
        return 0;
    }
}

bool ResourceManager::checkResources(int building) {
    // Checks if player has enough resources to build certain building.

    //Wäinölä
    if (building == 1) {
        if (getResource("money") >= 50) {
            return true;
        }
    //Mikontalo
    } else if (building == 3) {
        if (getResource("money") >= 150 && getResource("concrete") >= 50
                && getResource("mead") >= 50) {
            return true;
        }
    //Matriisintorni
    } else if (building == 4) {
        if (getResource("money") >= 300 && getResource("concrete") >= 500
            && getResource("mead") >= 450 && getResource("credits") >= 15) {
            return true;
        }
    //Tieteentorni
    } else if (building == 5) {
        if (getResource("money") >= 200 && getResource("concrete") >= 150
            && getResource("mead") >= 100 && getResource("credits") >= 4) {
            return true;
        }
    // Duo
    } else if (building == 6) {
        if (getResource("money") >= 120 && getResource("concrete") >= 100
            && getResource("mead") >= 75 && getResource("credits") >= 2) {
            return true;
        }
    }
    return false;
}

void ResourceManager::forceResource(QString res, int value) {
    if (resources_.contains(res)) {
        resources_[res] = value;
    }
}

