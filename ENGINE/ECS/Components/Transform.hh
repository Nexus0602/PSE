
struct TransformComponent {
    Vec2 position;
    double rotation;
    Vec2 scale;

    TransformComponent(Vec2 position = Vec2(0,0), double rotation = 0.0, Vec2 scale = Vec2(1,1)){
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;

    }
};

