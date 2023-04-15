struct HealthComponent {
    int health;
    int maxHealth;
    
    HealthComponent(int h = 100) : health(h), maxHealth(h) {}
};
