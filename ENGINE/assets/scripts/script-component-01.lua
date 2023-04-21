entities = {
    {
    group = "enemies",
    components = {
        transform = {
            position = {x=100, y=100},
            scale = {x=1.0 , y=1.0},
            rotation = 0.0,
        },
        kinematic = {
            velocity = {x=0, y=0},
            acceleration = {x=0, y=0},
            angularVelocity = {x=0, y=0},
            angularAcceleration = {x=0, y=0},
        }
        collider = {
            shape = "circle",
            radius =1,
            render = false
        },
        rigidbody = {
            mass=1,
            shape = "circle",
            radius =1,
            color = {r=252,g=186,b=3}
        },
        on_update_script = {
            function()
                print("Executing first Lua Script")
            end
        }
    }
},
...
}