/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef GRIM_GFX_OPENGL_H
#define GRIM_GFX_OPENGL_H

#include "engines/grim/gfx_base.h"

#ifdef USE_OPENGL

#if defined (SDL_BACKEND) && !defined(__amigaos4__)
#include <SDL_opengl.h>
#undef ARRAYSIZE
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace Grim {

class ModelNode;
class Mesh;
class MeshFace;

class GfxOpenGL : public GfxBase {
public:
	GfxOpenGL();
	virtual ~GfxOpenGL();

	byte *setupScreen(int screenW, int screenH, bool fullscreen) override;

	const char *getVideoDeviceName() override;

	void setupCamera(float fov, float nclip, float fclip, float roll) override;
	void positionCamera(const Math::Vector3d &pos, const Math::Vector3d &interest, float roll) override;

	Math::Matrix4 getModelView() override;
	Math::Matrix4 getProjection() override;

	void clearScreen() override;
	void clearDepthBuffer() override;
	void flipBuffer() override;

	bool isHardwareAccelerated() override;

	void getBoundingBoxPos(const Mesh *model, int *x1, int *y1, int *x2, int *y2) override;
	void getBoundingBoxPos(const EMIModel *model, int *x1, int *y1, int *x2, int *y2) override;

	void startActorDraw(const Actor *actor) override;
	void finishActorDraw() override;
	void setShadow(Shadow *shadow) override;
	void drawShadowPlanes() override;
	void setShadowMode() override;
	void clearShadowMode() override;
	void setShadowColor(byte r, byte g, byte b) override;
	void getShadowColor(byte *r, byte *g, byte *b) override;

	void set3DMode() override;

	void translateViewpointStart() override;
	void translateViewpoint(const Math::Vector3d &vec) override;
	void rotateViewpoint(const Math::Angle &angle, const Math::Vector3d &axis) override;
	void translateViewpointFinish() override;

	void drawEMIModelFace(const EMIModel *model, const EMIMeshFace *face) override;
	void drawModelFace(const Mesh *mesh, const MeshFace *face) override;
	void drawSprite(const Sprite *sprite) override;

	void enableLights() override;
	void disableLights() override;
	void setupLight(Light *light, int lightId) override;
	void turnOffLight(int lightId) override;

	void createMaterial(Texture *material, const char *data, const CMap *cmap, bool clamp) override;
	void selectMaterial(const Texture *material) override;
	void destroyMaterial(Texture *material) override;

	void createBitmap(BitmapData *bitmap) override;
	void drawBitmap(const Bitmap *bitmap, int x, int y, uint32 layer=0, float rot=0) override;
	void destroyBitmap(BitmapData *bitmap) override;

	void createFont(Font *font) override;
	void destroyFont(Font *font) override;

	void createTextObject(TextObject *text) override;
	void drawTextObject(const TextObject *text) override;
	void destroyTextObject(TextObject *text) override;

	Bitmap *getScreenshot(int w, int h) override;
	void storeDisplay() override;
	void copyStoredToDisplay() override;
	void dimScreen() override;
	void dimRegion(int x, int y, int w, int h, float level) override;
	void irisAroundRegion(int x1, int y1, int x2, int y2) override;

	void drawEmergString(int x, int y, const char *text, const Color &fgColor) override;
	void loadEmergFont() override;

	void drawRectangle(const PrimitiveObject *primitive) override;
	void drawLine(const PrimitiveObject *primitive) override;
	void drawPolygon(const PrimitiveObject *primitive) override;

	void prepareMovieFrame(Graphics::Surface *frame) override;
	void drawMovieFrame(int offsetX, int offsetY) override;
	void releaseMovieFrame() override;

	void createSpecialtyTextures() override;

    // special
    bool worldToScreen(const Math::Vector3d &vec, int& x, int &y);
    bool raycast(int x, int y, Math::Vector3d &r0, Math::Vector3d &r1);
    void blackbox(int x0, int y0, int x1, int y1, float opacity);
protected:
	void drawDepthBitmap(int x, int y, int w, int h, char *data);
	void initExtensions();
private:
	GLuint _emergFont;
	int _smushNumTex;
	GLuint *_smushTexIds;
	int _smushWidth;
	int _smushHeight;
	byte *_storedDisplay;
	bool _useDepthShader;
	GLuint _fragmentProgram;
	bool _useDimShader;
	GLuint _dimFragProgram;
	GLint _maxLights;
	float _alpha;
	const Actor *_currentActor;
	GLenum _depthFunc;
};

} // end of namespace Grim

#endif

#endif
