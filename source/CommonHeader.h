//
//  CommonHeader.h
//  MacTerminal
//
//  Created by yinquan on 2023/6/15.
//

#ifndef CommonHeader_h
#define CommonHeader_h
#include <string>
#include <map>
#include <vector>

#define QYColor(r, g, b, a) a + (b << 8) + (g << 16) + (r << 24)
#define QYColorRGBA_R(color) color >> 24
#define QYColorRGBA_G(color) (color >> 16) & 255
#define QYColorRGBA_B(color) (color >> 8) & 255
#define QYColorRGBA_A(color) color & 255
#endif /* CommonHeader_h */
