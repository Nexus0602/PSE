using namespace std;
struct RectangleShape: public PolygonShape{
    float width;
    float height;

    RectangleShape(std::vector <Vec2> vertices){

        worldVertices.push_back(vertices[0]);
        worldVertices.push_back(vertices[1]);
        worldVertices.push_back(vertices[2]);
        worldVertices.push_back(vertices[3]);

        std::cout<< "V1 "<<worldVertices[0] << endl;

    }

    RectangleShape(int width, int height, Color color, bool filled){

        this->width=width;
        this->height=height;
        this->color=color;
        this->filled=filled;

        localVertices.push_back(Vec2(-width/2.0, -height /2.0));
        localVertices.push_back(Vec2(+width/2.0, -height /2.0));
        localVertices.push_back(Vec2(+width/2.0, +height /2.0));
        localVertices.push_back(Vec2(-width/2.0, +height /2.0));

        worldVertices.push_back(Vec2(-width /2.0, -height/2.0 ));
        worldVertices.push_back(Vec2(+width /2.0, -height/2.0 ));
        worldVertices.push_back(Vec2(+width /2.0, +height/2.0 ));
        worldVertices.push_back(Vec2(-width /2.0, +height/2.0 ));


    }

    Shape* Clone() const override{

        return new RectangleShape(width,height,color,filled);

    }
    ShapeType GetType()const override {

        return RECTANGLE;
    }
    float GetMomentOfInertia() const override{
        return (0.083333)*(width*width+height*height);
    }

    void Render(TransformComponent transform)const override {

        if(this->filled)
            Graphics::DrawFillRect(
                transform.position.x,
                transform.position.y,
                this->width,
                this->height,
                this->color
            );
        else
        //DrawPolugon
            Graphics::DrawPolygon(
                transform.position.x,
                transform.position.y,
                this->worldVertices,
                this->color
            );
    }

    void UpdateVertices(double rotation, Vec2 position) const override{
        // Actualizar los vértices locales

        Vec2 center(0.0f, 0.0f);
        for (const auto& vertex : localVertices) {
            center += vertex;
        }

        center /= static_cast<float>(localVertices.size());
        vector<Vec2> rotatedVertices;
        for (const auto& vertex : localVertices) {
            Vec2 distance = vertex - center;
            float x = cos(rotation) * distance.x - sin(rotation) * distance.y;
            float y = sin(rotation) * distance.x + cos(rotation) * distance.y;
            rotatedVertices.push_back(Vec2(x, y) + center);
        }

        worldVertices = rotatedVertices;
        //return new RectangleShape (aux);
        //cos(rotation), -sin(rotation), sin(rotation), cos(rotation)
    }
};