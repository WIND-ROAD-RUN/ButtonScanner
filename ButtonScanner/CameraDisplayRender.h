#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QImage>

class CameraDisplayRender : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit CameraDisplayRender(QWidget* parent = nullptr)
        : QOpenGLWidget(parent), texture(nullptr) {
    }

    ~CameraDisplayRender() {
        makeCurrent();
        delete texture;
        doneCurrent();
    }

    void setImage(const QImage& image) {
        makeCurrent();
        if (texture) {
            delete texture;
            texture = nullptr;
        }
        texture = new QOpenGLTexture(image.mirrored());
        texture->setMinificationFilter(QOpenGLTexture::Linear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        doneCurrent();
        update(); // 触发重绘
    }

protected:
    void initializeGL() override {
        initializeOpenGLFunctions();
        glEnable(GL_TEXTURE_2D);
    }

    void resizeGL(int w, int h) override {
        glViewport(0, 0, w, h);
    }

    void paintGL() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (texture) {
            texture->bind();
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
            glEnd();
            texture->release();
        }
    }

private:
    QOpenGLTexture* texture;
};