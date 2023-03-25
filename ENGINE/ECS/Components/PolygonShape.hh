struct PolygonShape: public Shape{

    std::vector<Vec2> localVertices;
    mutable std::vector<Vec2> worldVertices;

    PolygonShape()=default;
    PolygonShape(std::vector <Vec2> vertices);

    virtual Shape* Clone() const=0;
    virtual ShapeType GetType  ()const =0;
    virtual float GetMomentOfInertia() const =0;
    virtual void UpdateVertices(double, Vec2)const =0;
};
