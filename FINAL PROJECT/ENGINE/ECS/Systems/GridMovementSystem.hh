class GridMovementSystem {
    public:
        void OnKeyDown(const KeyDownEvent& keyDown) noexcept {
        auto view = keyDown.world->view<TransformComponent, GridMovementComponent>();
        for (auto entity: view){
            auto& transform = view.get<TransformComponent>(entity);
            const auto grid = view.get<GridMovementComponent>(entity);

            Vec2 direction;
            switch (keyDown.symbol){
                case SDLK_UP:
                direction = Vec2(0,-1);
                break;
                case SDLK_RIGHT:
                direction = Vec2(1,0);
                break;
                case SDLK_LEFT:
                direction = Vec2(-1,0);
                break;
                case SDLK_DOWN:
                direction = Vec2(0,1);
                break;
            }

            transform.position += direction * grid.stepSize;
        }
    }
};