#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <vector>
#include <cmath>

using namespace std;

struct Point
{
	Point() : x(0), y(0), dx(0), dy(0) {}
	Point(float vx, float vy) : x(vx), y(vy), dx(0), dy(0) {}
	float x, y;
	float dx, dy;
};

class Net
{
public:
	Net() : m_index(0), m_intensity(0.2f), m_lastIndex(-1) {}
	~Net() {}

	bool initNet(int w, int h)
	{
		if(w < 2 || h < 2)
			return false;

		m_width = w;
		m_height = h;

		m_vec[0].resize(w * h);
		m_vec[1].resize(w * h);
		float widthStep = 1.0f / (w - 1);
		float heightStep = 1.0f / (h - 1);

		for(int i = 0; i != h; ++i)
		{
			const float heightI = i * heightStep;
			int index = w * i;
			for(int j = 0; j != w; ++j)
			{
				const float widthJ = j * widthStep;
				m_vec[0][index] = Point(widthJ, heightI);
				m_vec[1][index] = Point(widthJ, heightI);
				++index;
			}
		}
		return true;
	}

	void update()
	{
		const float widthStep = 1.0f / (m_width - 1.0f);
		const float heightStep = 1.0f / (m_height - 1.0f);
		int index = (m_index + 1) % 2;

		for(int i = 1; i < m_height - 1; ++i)
		{
			//const float heightI = i * heightStep;
			const int k = m_width * i;
			for(int j = 1; j < m_width - 1; ++j)
			{
				const int h = k + j;
				float dx, dy;
				dx = (m_vec[m_index][h - 1].x + m_vec[m_index][h + 1].x - m_vec[m_index][h].x * 2.0f);
				dy = (m_vec[m_index][h - 1].y + m_vec[m_index][h + 1].y - m_vec[m_index][h].y * 2.0f);

				dx += (m_vec[m_index][h - m_width].x + m_vec[m_index][h + m_width].x - m_vec[m_index][h].x * 2.0f);
				dy += (m_vec[m_index][h - m_width].y + m_vec[m_index][h + m_width].y - m_vec[m_index][h].y * 2.0f);

				//模拟能量损失， 当加速度方向与速度方向相反时，加快减速
				if(((unsigned&)dx >> 31) != ((unsigned&)m_vec[m_index][h].dx >> 31))
					dx *= 1.0f + m_intensity;
				
				if(((unsigned&)dy >> 31) != ((unsigned&)m_vec[m_index][h].dy >> 31))
					dy *= 1.0f + m_intensity;

				m_vec[m_index][h].dx += dx * m_intensity;
				m_vec[m_index][h].dy += dy * m_intensity;
				m_vec[index][h].dx = m_vec[m_index][h].dx;
				m_vec[index][h].dy = m_vec[m_index][h].dy;

				m_vec[index][h].x = m_vec[m_index][h].x + m_vec[index][h].dx;
				m_vec[index][h].y = m_vec[m_index][h].y + m_vec[index][h].dy;
			}
		}
		m_index = index;
	}

	void catchPoint(float x, float y)
	{
		int index;

		if(m_lastIndex < 0)
		{
			float mdis = 1e9f;
			for(int i = 1; i < m_height - 1; ++i)
			{
				const int k = m_width * i;
				for(int j = 1; j < m_width - 1; ++j)
				{
					const int h = k + j;
					const float dis = fabsf(x - m_vec[m_index][h].x) + fabsf(y - m_vec[m_index][h].y);
					if(dis < mdis)
					{
						index = h;
						mdis = dis;
					}
				}
			}
			m_lastIndex = index;
		}
		else
			index = m_lastIndex;

		m_vec[0][index].x = x;
		m_vec[0][index].y = y;
		m_vec[1][index].x = x;
		m_vec[1][index].y = y;
		m_vec[0][index].dx = 0.0f;
		m_vec[0][index].dy = 0.0f;
		m_vec[1][index].dx = 0.0f;
		m_vec[1][index].dy = 0.0f;
	}

	void releasePoint()
	{
		m_lastIndex = -1;
	}

	void drawNet(float width, float height)
	{
		auto &v = m_vec[m_index];
		for(int i = 0; i != m_height; ++i)
		{
			const int k = i * m_width;
			for(int j = 1; j != m_width; ++j)
			{
				const int h = k + j;
				line(v[h - 1].x * width, v[h - 1].y * height, v[h].x * width, v[h].y * height);
			}
		}

		for(int i = 0; i != m_width; ++i)
		{
			for(int j = 1; j != m_height; ++j)
			{
				const int h2 = j * m_width + i;
				const int h1 = (j - 1) * m_width + i;
				line(v[h1].x * width, v[h1].y * height, v[h2].x * width, v[h2].y * height);
			}
		}
	}

	void intensityInc(float f)
	{
		m_intensity += f;
		if(m_intensity > 0.3f)
			m_intensity = 0.3f;
	}

	void intensityDec(float f)
	{
		m_intensity -= f;
		if(m_intensity < 0.001f)
			m_intensity = 0.001f;
	}

	float getIntensity()
	{
		return m_intensity;
	}

private:
	vector<Point> m_vec[2];
	int m_index;
	int m_width, m_height;
	float m_intensity;
	int m_lastIndex;
};

int main()
{
	initgraph(800, 600, INIT_RENDERMANUAL);
	setcaption("EGE网格 By wysaid");
	Net net;
	char buffer[1024];

	sprintf(buffer, "当前网格强度：%g", net.getIntensity());

	net.initNet(80, 60);

	for(; is_run(); delay_fps(60))
	{
		cleardevice();
		if(keystate(key_mouse_l))
		{
			int x, y;
			mousepos(&x, &y);
			net.catchPoint(x / 800.0f, y / 600.0f);
		}
		else
			net.releasePoint();

		if(kbhit())
		{
			switch(getch())
			{
			case '+':
				net.intensityInc(0.005f);
				break;
			case '-':
				net.intensityDec(0.005f);
				break;
			case 27:
				exit(0);
			}
			flushkey();
			sprintf(buffer, "当前网格强度：%g", net.getIntensity());
		}

		setcolor(GREEN);
		net.drawNet(800, 600);
		net.update();
		setcolor(0x00ff0000);
		outtextxy(10, 10, "按'+'或者'-'可以增大或者减小网格弹力！这个版本由wysaid制作， 参见: http://blog.wysaid.org");
		outtextxy(10, 30, buffer);
	}

	closegraph();
	return 0;
}