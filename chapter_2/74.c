int tsub_ok(int x, int y)
{
	int sub = x - y;
	int is_overflowed = (x > 0 && y < 0 && sub < 0) || (x < 0 && y > 0
							    && sub > 0);
	return !is_overflowed;
}
