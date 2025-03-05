## TODO
### General
- Create a better system for handling file paths. Something like `loadAsset(name)` etc...
- Add documentation.
- Find a better place to init SDL than the renderer. Renderer may be a temporary object, don't want to have to reinit SDL each time...

### EventHandler
- Make it not a singleton.
- Refactor it to an input handler maybe?

### AssetManager
- Should this class have a member of SDL_Renderer or a wrapper thereof?
- Add a failsafe/fallback texture for any failed loading of textures.

### Map
- Finish the MapSerializer !!
- Should TileMap have multiple layers for maps with more than 1 depth level? 
- New Rendering and update loop for the new tile map system.
- Make a constant or sumn for the empty tile.

### ECS
- Draft an ECS bzw. figure out how it can be implemented.
- Maybe this can be combined with map, have TileEntity for example inheriting from Entity. (still static and dynamic stuff)