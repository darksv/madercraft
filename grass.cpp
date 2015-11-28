#include "grass.hpp"

BlockGrass::BlockGrass()
	: BlockModel(new Texture("textures\\cube_top.raw"), new Texture("textures\\cube_bottom.raw"), new Texture("textures\\cube_side.raw"), new Shader("shaders\\cube.vs", "shaders\\cube.frag"))
{

}