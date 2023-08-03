﻿using System;

using Paper;

namespace Sandbox
{
    public class Player : Entity
    {
        private TransformComponent transformComponent;
        private SpriteComponent spriteComponent;

        public override void OnCreate()
        {
            transformComponent = GetComponent<TransformComponent>();
            spriteComponent = GetComponent<SpriteComponent>();
        }

        public override void OnDestroy()
        {
        }

        private int lol = 1;

        public override void OnUpdate(float dt)
        {
            float speed = 2.0f;

            Vec3 pos = transformComponent.Position;

            if (Input.IsKeyDown(Key.W))
            {
                pos.Z -= speed * dt;
            }
            if (Input.IsKeyDown(Key.A))
            {
                pos.X -= speed * dt;
            }
            if (Input.IsKeyDown(Key.S))
            {
                pos.Z += speed * dt;
            }
            if (Input.IsKeyDown(Key.D))
            {
                pos.X += speed * dt;
            }
            if (Input.IsKeyDown(Key.E))
                pos.Y += speed * dt;
            if (Input.IsKeyDown(Key.Q))
                pos.Y -= speed * dt;

            pos.X += speed * dt;

            transformComponent.Position = pos;

            

            if (Input.IsKeyReleased(Key.P))
            {
                spriteComponent.Texture = new Texture("assets/textures/putain.jpg");
                transformComponent.Scale = new Vec3(2.0f, 2.0f, 1.0f);
                spriteComponent.Geometry = Geometry.Circle;
                spriteComponent.Color = new Vec4(1.0f, 0.0f, 0.0f, 1.0f);
                spriteComponent.TilingFactor = lol++;
            }
        }
    }
}