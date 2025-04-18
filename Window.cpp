#include "Window.h"

Window::Window(int w, int h, int flag)
{
    m_handle = ::initgraph(w, h, flag);
    ::setbkmode(TRANSPARENT);
}

void Window::setWindowTitle(const std::string& title)
{
    ::SetWindowText(m_handle, title.c_str());
}

int Window::exec()
{
    return 0;
}

int Window::width()
{
    return ::getwidth();
}

int Window::height()
{
    return ::getheight();
}

void Window::clear()
{
    ::cleardevice();
}

void Window::beginDraw()
{
    ::BeginBatchDraw();

}

void Window::flushDraw()
{
    ::FlushBatchDraw();
}

void Window::endDraw()
{
    ::EndBatchDraw();
}
