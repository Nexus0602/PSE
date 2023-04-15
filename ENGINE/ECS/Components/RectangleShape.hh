using namespace std;
struct RectangleShape: public PolygonShape{
    float width;
    float height;

    RectangleShape(std::vector <Vec2> vertices){

        worldVertices.push_back(vertices[0]);
        worldVertices.push_back(vertices[1]);
        worldVertices.push_back(vertices[2]);
        worldVertices.push_back(vertices[3]);

       //std::cout<< "V1 "<<worldVertices[0] << endl;

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

        worldVertices.push_back(Vec2(-width /2.0, -height/2.0 )); //superior izq
        worldVertices.push_back(Vec2(+width /2.0, -height/2.0 )); // superior derecho
        worldVertices.push_back(Vec2(+width /2.0, +height/2.0 )); // ind dch
        worldVertices.push_back(Vec2(-width /2.0, +height/2.0 )); //inf izq


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

        //std::cout<<"RENDER"<<std::endl;
        //std::cout<<transform.position<<std::endl;
        /*std::cout<<worldVertices[0]<<std::endl;
        std::cout<<worldVertices[1]<<std::endl;
        std::cout<<worldVertices[2]<<std::endl;
        std::cout<<worldVertices[3]<<std::endl;*/

        if(this->filled)
            Graphics::DrawFillRect(
                transform.position.x,
                transform.position.y,
                this->width,
                this->height,
                this->color
            );
        else
        //DrawPolygon
        Graphics::DrawRect(
            transform.position.x,
                transform.position.y,
                this->width,
                this->height,
                this->color
        );
            /*Graphics::DrawPolygon(
                transform.position.x,
                transform.position.y,
                this->worldVertices,
                this->color
            );*/
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

    void UpdatePositions(Vec2 position) const override {
        Vec2 center(0.0f, 0.0f);
        for (const auto& vertex : localVertices) {
            center += vertex;
        }
        center /= static_cast<float>(localVertices.size());
        
        vector<Vec2> updatedVertices;
        for (const auto& vertex : localVertices) {
            Vec2 v = vertex - center;
            v += position;
            updatedVertices.push_back(v);
        }
        worldVertices = updatedVertices;
    }

    Vec2 EdgeAt(int n) const override {
        int count = static_cast<int>(this->worldVertices.size());
        Vec2 v1 = this->worldVertices[n];
        Vec2 v2 = this->worldVertices[(n + 1) % count];  // Si n es el último índice, tomamos el vértice 0
        Vec2 edgeVec = v2 - v1;
        Vec2 normal = edgeVec.Normal().Perpendicular();

        return normal;
    }


    float FindMinSeparation( PolygonShape* other, Vec2& axis, Vec2& point) const override {

        float separation = std::numeric_limits<float>::lowest();

        for (int i = 0; i< static_cast<int>(this->worldVertices.size());i++){
            //std::cout<<i<<endl;
            Vec2 va = this->worldVertices[i]/50;
            //std::cout<<"va " <<va<<std::endl;
            Vec2 normal = this->EdgeAt(i).Normal();
            //std::cout<<"Normal " <<normal<<endl;

            float minSep = std::numeric_limits<float>::max();
            Vec2 minVertex;

            for (int j =0 ; j<static_cast<int>(other->worldVertices.size());j++){
                Vec2 vb = other->worldVertices[j]/50;
                //std::cout<<"vb " <<vb<<std::endl;
                Vec2 projectionv = (vb-va);
                //std::cout<<"projection " <<projectionv <<std::endl;
                float projection = projectionv.Dot(normal);
                //std::cout<<"projection " <<projection<<std::endl;
                

                if (projection < minSep){
                    minSep = projection;
                    minVertex = vb;
                }
            }

            if (minSep > separation){
                separation = minSep;
                axis = this->EdgeAt(i);
                point = minVertex;
            }
        }
        //std::cout << "Separation "<< separation << std::endl;
        return separation;

    }


};