#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SceneObject {
public:
    string name;

    SceneObject(const string& objName) : name(objName) {}
};

class SceneCollectionBox {
private:
    vector<SceneObject> objects;
    int numObjects;

public:
    SceneCollectionBox() : numObjects(0) {}

    void addObject(const SceneObject& object) {
        objects.push_back(object);
        numObjects++;
    }

    void removeObject(const SceneObject& object) {
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            if (it->name == object.name) {
                objects.erase(it);
                numObjects--;
                break;
            }
        }
    }

    int getNumObjects() const {
        return numObjects;
    }

    void printObjects() const {
        for (const auto& object : objects) {
            cout << object.name << endl;
        }
    }
};

int main() {
    SceneCollectionBox collection;

    // Add objects to the collection
    SceneObject obj1("Object 1");
    SceneObject obj2("Object 2");
    SceneObject obj3("Object 3");

    collection.addObject(obj1);
    collection.addObject(obj2);
    collection.addObject(obj3);

    // Remove an object from the collection
    collection.removeObject(obj2);

    // Print the number of objects and the remaining objects in the collection
    cout << "Number of objects: " << collection.getNumObjects() << endl;
    collection.printObjects();

    return 0;
}
