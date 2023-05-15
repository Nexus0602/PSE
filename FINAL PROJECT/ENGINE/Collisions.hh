struct Contact {

    entt::entity a;
    entt::entity b;

    Vec2 start;
    Vec2 end;
    Vec2 normal;
    float depth;

};

struct Collisions {

    static bool IsColliding(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world);
    static bool IsCollidingCircleCircle(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world);
    static bool IsCollidingPolygonPolygon(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world);

};