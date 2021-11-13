
ushort scan_leds = 1;
void scanner()
{
    scan_leds <<= 1;
    if (scan_leds == 0)
        scan_leds = 1;

    P0 = ~(scan_leds & 0xff);
    P2 = ~(scan_leds >> 8);

    sleep(10000);
}

void scanner_back()
{
    scan_leds >>= 1;
    if (scan_leds == 0)
        scan_leds = (ushort)1 << 15;

    P0 = ~(scan_leds & 0xff);
    P2 = ~(scan_leds >> 8);

    sleep(10000);
}