
struct CircleShape:public Shape{
    float radius;

    CircleShape(int radius, Color color, bool filled){
        this->radius=radius;
        this->color=color;
        this->filled=filled;

    }
    Shape* Clone() const{

        return new CircleShape(radius,color,filled);
    }
    
    ShapeType GetType()const{
        return CIRCLE;
    }
    float GetMomentOfInertia() const{

        return 0.5*(radius*radius);
    }
    void Render(TransformComponent transform)const override{
        if(this->filled)
        {
            Graphics::DrawFillCircle(
                transform.position.x,
                transform.position.y,
                this->radius,
                this->color
            );
        }
        else
            Graphics::DrawCircle(
                transform.position.x,
                transform.position.y,
                this->radius,
                this->color,
                transform.rotation
            );
    }



};