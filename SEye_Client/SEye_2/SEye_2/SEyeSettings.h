class Settings
{
public:
	static bool InvertY;
	static bool InvertX;
	static float OffsetX;
	static float OffsetY;
	static float ScaleX;
	static float ScaleY;
	static float RotationOffset;

	static bool LoadINI(const char *Map);
};