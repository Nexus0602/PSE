class SpriteSystem {
    public:
    void Render(entt::registry& world){
        auto view = world.view<TransformComponent, SpriteComponent>();
        for (auto entity : view) {
            const auto t = view.get<TransformComponent>(entity);
            const auto s = view.get<SpriteComponent>(entity);
            SDL_Texture* texture = Graphics::GetTexture(s.assetId);

            //std::cout<<s.assetId<<std::endl;
            Graphics::DrawSprite(texture, t.position, t.scale, s.width, s.height, t.rotation, s.srcRect);

            //std::cout<<s.width<<std::endl;

        }
    }
};