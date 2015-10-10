# ArcEngine
ArcEngine is a entity component system (ECS) game engine for creating 2D games. It is written in C++11 and requires EntityX and SFML 2.
## Features
Stack State Machine.

Entity Component System (EntityX).

Resource Management with XML parsing (tinyXML2).

Input Management with control mapping.

Scene Graph System, Rendering System, and other core Systems.

## Why?
With the advent of modern C++, writing game logic can be just as pleasant (and simple) as using a scripting language.
I created this project to provide a 'hopefully' minimal core feature set for creating complex 2D games.

## How?
1. Clone the repo.
2. Configure your project's build system to link to EntityX and SFML 2.3.
3. Create (or modify) a game state, which inherits the State class.
4. Add your game logic to the State callbacks: onHandleEvent, onUpdate, onDraw and others.

## Example
The following snippet shows the creation of two entities. Both parent 'e' and child 'c' will be rendered in the scene.
```
MainMenuState::MainMenuState(Arc::Context context)
: State(context)
{
	auto e = getEntityManager().create();
	e.assign<CNode>(100, 100);
	e.assign<CRenderSprite>(sf::Sprite(mContext.resources->getTexture("MyTextureID")));

	auto c = getEntityManager().create();
	c.assign<CNode>();
	e.assign<CRenderCirc>(sf::CircleShape(100));
	e.component<CNode>()->addChild(c);

	addToLayer(State::Layers::FOREGROUND, e);
}
```

Create the engine and push your first state! 'main.cpp'
```
try
{
    Arc::Engine game;
    game.pushState<MainMenuState>();
    game.run();
}
catch(std::exception& e)
{
    std::cout << "\nFatal Exception: " << e.what() << std::endl;
    return -1;
}
```
