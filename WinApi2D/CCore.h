#pragma once

class CTexture;

class CCore
{
	SINGLETON(CCore);

public:
	void update();
	void render();
	void init();
};

