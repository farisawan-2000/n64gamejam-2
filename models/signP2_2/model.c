#include <ultra64.h>
#include <gbi.h>
#include <PR/gt.h>
#include "n64_defs.h"
#include "gtHelpers.h"
extern Object2639 SignP2_2_Obj;
Object2639 *SignP2_2_objp = &SignP2_2_Obj;
static
Vtx sign_Cube_mesh_vtx_0[412] = {
	{{{-70, -48, 8},0, {290, -899},{0xF3, 0xEC, 0x7D, 0xFF}}},
	{{{-70, -46, 8},0, {290, -908},{0xF3, 0xEC, 0x7D, 0xFF}}},
	{{{-72, -46, 8},0, {272, -899},{0xF3, 0xEC, 0x7D, 0xFF}}},
	{{{-70, 46, 8},0, {1278, -1155},{0xF3, 0x14, 0x7D, 0xFF}}},
	{{{-70, 48, 8},0, {1296, -1155},{0xF3, 0x14, 0x7D, 0xFF}}},
	{{{-72, 46, 8},0, {1278, -1164},{0xF3, 0x14, 0x7D, 0xFF}}},
	{{{-70, -48, -8},0, {290, -661},{0xF3, 0xEC, 0x83, 0xFF}}},
	{{{-72, -46, -8},0, {272, -661},{0xF3, 0xEC, 0x83, 0xFF}}},
	{{{-70, -46, -8},0, {290, -652},{0xF3, 0xEC, 0x83, 0xFF}}},
	{{{-70, 48, -8},0, {1287, -405},{0xF3, 0x14, 0x83, 0xFF}}},
	{{{-70, 46, -8},0, {1296, -405},{0xF3, 0x14, 0x83, 0xFF}}},
	{{{-72, 46, -8},0, {1278, -396},{0xF3, 0x14, 0x83, 0xFF}}},
	{{{70, -48, 8},0, {766, -899},{0xD, 0xEC, 0x7D, 0xFF}}},
	{{{72, -46, 8},0, {784, -899},{0xD, 0xEC, 0x7D, 0xFF}}},
	{{{70, -46, 8},0, {766, -908},{0xD, 0xEC, 0x7D, 0xFF}}},
	{{{70, 48, 8},0, {1287, -917},{0xD, 0x14, 0x7D, 0xFF}}},
	{{{70, 46, 8},0, {1296, -917},{0xD, 0x14, 0x7D, 0xFF}}},
	{{{72, 46, 8},0, {1278, -908},{0xD, 0x14, 0x7D, 0xFF}}},
	{{{70, -48, -8},0, {766, -661},{0xD, 0xEC, 0x83, 0xFF}}},
	{{{70, -46, -8},0, {766, -652},{0xD, 0xEC, 0x83, 0xFF}}},
	{{{72, -46, -8},0, {784, -661},{0xD, 0xEC, 0x83, 0xFF}}},
	{{{70, 48, -8},0, {1287, -661},{0xD, 0x14, 0x83, 0xFF}}},
	{{{72, 46, -8},0, {1296, -661},{0xD, 0x14, 0x83, 0xFF}}},
	{{{70, 46, -8},0, {1278, -652},{0xD, 0x14, 0x83, 0xFF}}},
	{{{64, -43, 8},0, {2036, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{64, 43, 8},0, {2036, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-64, 43, 8},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-64, -43, 8},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{75, -43, -7},0, {820, -670},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{75, 43, -7},0, {1260, -670},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{75, 43, 7},0, {1260, -890},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{75, -43, 7},0, {820, -890},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-230, -9, -7},0, {992, -378},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-230, -9, 7},0, {992, -158},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-230, 10, 7},0, {1091, -158},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-230, 10, -7},0, {1091, -378},{0x81, 0x0, 0x0, 0xFF}}},
	{{{64, 50, -7},0, {1332, -670},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-64, 50, -7},0, {1772, -670},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-64, 50, 7},0, {1772, -890},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{64, 50, 7},0, {1332, -890},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-75, -43, 7},0, {820, -158},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-75, -9, 7},0, {992, -158},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-75, -9, -7},0, {992, -378},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-75, -43, -7},0, {820, -378},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-64, -43, -8},0, {2040, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-64, 43, -8},0, {2040, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{64, 43, -8},0, {-16, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{64, -43, -8},0, {-16, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-64, -50, 7},0, {308, -890},{0xF5, 0xBA, 0x6A, 0xFF}}},
	{{{-64, -49, 8},0, {308, -899},{0xF5, 0xBA, 0x6A, 0xFF}}},
	{{{-70, -48, 8},0, {290, -899},{0xF5, 0xBA, 0x6A, 0xFF}}},
	{{{-70, -49, 7},0, {290, -890},{0xF5, 0xBA, 0x6A, 0xFF}}},
	{{{-64, -49, 8},0, {308, -899},{0xFD, 0xEC, 0x7D, 0xFF}}},
	{{{-64, -47, 8},0, {308, -908},{0xFD, 0xEC, 0x7D, 0xFF}}},
	{{{-70, -46, 8},0, {290, -908},{0xFD, 0xEC, 0x7D, 0xFF}}},
	{{{-70, -48, 8},0, {290, -899},{0xFD, 0xEC, 0x7D, 0xFF}}},
	{{{-64, -43, 8},0, {820, -1146},{0xFD, 0xFB, 0x7F, 0xFF}}},
	{{{-70, -43, 8},0, {820, -1155},{0xFD, 0xFB, 0x7F, 0xFF}}},
	{{{-70, -46, 8},0, {802, -1155},{0xFD, 0xFB, 0x7F, 0xFF}}},
	{{{-64, -47, 8},0, {802, -1146},{0xFD, 0xFB, 0x7F, 0xFF}}},
	{{{-70, -43, 8},0, {820, -142},{0xF3, 0xFB, 0x7E, 0xFF}}},
	{{{-74, -43, 8},0, {820, -140},{0xF3, 0xFB, 0x7E, 0xFF}}},
	{{{-72, -46, 8},0, {802, -140},{0xF3, 0xFB, 0x7E, 0xFF}}},
	{{{-70, -46, 8},0, {802, -144},{0xF3, 0xFB, 0x7E, 0xFF}}},
	{{{-75, -43, 7},0, {820, -158},{0xCD, 0xED, 0x73, 0xFF}}},
	{{{-74, -47, 7},0, {802, -158},{0xCD, 0xED, 0x73, 0xFF}}},
	{{{-72, -46, 8},0, {802, -149},{0xCD, 0xED, 0x73, 0xFF}}},
	{{{-74, -43, 8},0, {820, -149},{0xCD, 0xED, 0x73, 0xFF}}},
	{{{-74, -47, 7},0, {276, -890},{0xD8, 0xC3, 0x68, 0xFF}}},
	{{{-70, -49, 7},0, {272, -890},{0xD8, 0xC3, 0x68, 0xFF}}},
	{{{-70, -48, 8},0, {272, -899},{0xD8, 0xC3, 0x68, 0xFF}}},
	{{{-72, -46, 8},0, {281, -899},{0xD8, 0xC3, 0x68, 0xFF}}},
	{{{-64, 43, 8},0, {1260, -1146},{0xFD, 0x5, 0x7F, 0xFF}}},
	{{{-64, 47, 8},0, {1278, -1146},{0xFD, 0x5, 0x7F, 0xFF}}},
	{{{-70, 46, 8},0, {1278, -1155},{0xFD, 0x5, 0x7F, 0xFF}}},
	{{{-70, 43, 8},0, {1260, -1155},{0xFD, 0x5, 0x7F, 0xFF}}},
	{{{-64, 47, 8},0, {1278, -1146},{0xFD, 0x14, 0x7D, 0xFF}}},
	{{{-64, 49, 8},0, {1296, -1146},{0xFD, 0x14, 0x7D, 0xFF}}},
	{{{-70, 48, 8},0, {1296, -1155},{0xFD, 0x14, 0x7D, 0xFF}}},
	{{{-70, 46, 8},0, {1278, -1155},{0xFD, 0x14, 0x7D, 0xFF}}},
	{{{-64, 50, 7},0, {1772, -890},{0xF5, 0x46, 0x6A, 0xFF}}},
	{{{-70, 49, 7},0, {1790, -890},{0xF5, 0x46, 0x6A, 0xFF}}},
	{{{-70, 48, 8},0, {1790, -899},{0xF5, 0x46, 0x6A, 0xFF}}},
	{{{-64, 49, 8},0, {1772, -899},{0xF5, 0x46, 0x6A, 0xFF}}},
	{{{-70, 49, 7},0, {1292, -158},{0xD8, 0x3D, 0x68, 0xFF}}},
	{{{-74, 47, 7},0, {1296, -158},{0xD8, 0x3D, 0x68, 0xFF}}},
	{{{-72, 46, 8},0, {1296, -149},{0xD8, 0x3D, 0x68, 0xFF}}},
	{{{-70, 48, 8},0, {1287, -149},{0xD8, 0x3D, 0x68, 0xFF}}},
	{{{-75, 43, 7},0, {1260, -158},{0xCD, 0x13, 0x73, 0xFF}}},
	{{{-74, 43, 8},0, {1260, -149},{0xCD, 0x13, 0x73, 0xFF}}},
	{{{-72, 46, 8},0, {1278, -149},{0xCD, 0x13, 0x73, 0xFF}}},
	{{{-74, 47, 7},0, {1278, -158},{0xCD, 0x13, 0x73, 0xFF}}},
	{{{-74, 43, 8},0, {1260, -149},{0xF3, 0x5, 0x7E, 0xFF}}},
	{{{-70, 43, 8},0, {1260, -140},{0xF3, 0x5, 0x7E, 0xFF}}},
	{{{-70, 46, 8},0, {1278, -140},{0xF3, 0x5, 0x7E, 0xFF}}},
	{{{-72, 46, 8},0, {1278, -149},{0xF3, 0x5, 0x7E, 0xFF}}},
	{{{-64, -50, -7},0, {308, -670},{0xF5, 0xBA, 0x96, 0xFF}}},
	{{{-70, -49, -7},0, {290, -670},{0xF5, 0xBA, 0x96, 0xFF}}},
	{{{-70, -48, -8},0, {290, -661},{0xF5, 0xBA, 0x96, 0xFF}}},
	{{{-64, -49, -8},0, {308, -661},{0xF5, 0xBA, 0x96, 0xFF}}},
	{{{-70, -49, -7},0, {290, -670},{0xD8, 0xC3, 0x98, 0xFF}}},
	{{{-74, -47, -7},0, {272, -670},{0xD8, 0xC3, 0x98, 0xFF}}},
	{{{-72, -46, -8},0, {272, -661},{0xD8, 0xC3, 0x98, 0xFF}}},
	{{{-70, -48, -8},0, {290, -661},{0xD8, 0xC3, 0x98, 0xFF}}},
	{{{-75, -43, -7},0, {820, -378},{0xCD, 0xED, 0x8D, 0xFF}}},
	{{{-74, -43, -8},0, {820, -387},{0xCD, 0xED, 0x8D, 0xFF}}},
	{{{-72, -46, -8},0, {802, -387},{0xCD, 0xED, 0x8D, 0xFF}}},
	{{{-74, -47, -7},0, {802, -378},{0xCD, 0xED, 0x8D, 0xFF}}},
	{{{-74, -43, -8},0, {820, -387},{0xF3, 0xFB, 0x82, 0xFF}}},
	{{{-70, -43, -8},0, {820, -396},{0xF3, 0xFB, 0x82, 0xFF}}},
	{{{-70, -46, -8},0, {802, -396},{0xF3, 0xFB, 0x82, 0xFF}}},
	{{{-72, -46, -8},0, {802, -387},{0xF3, 0xFB, 0x82, 0xFF}}},
	{{{-64, -43, -8},0, {820, -414},{0xFD, 0xFB, 0x81, 0xFF}}},
	{{{-64, -47, -8},0, {802, -414},{0xFD, 0xFB, 0x81, 0xFF}}},
	{{{-70, -46, -8},0, {802, -405},{0xFD, 0xFB, 0x81, 0xFF}}},
	{{{-70, -43, -8},0, {820, -405},{0xFD, 0xFB, 0x81, 0xFF}}},
	{{{-64, -47, -8},0, {308, -654},{0xFD, 0xEC, 0x83, 0xFF}}},
	{{{-64, -49, -8},0, {308, -652},{0xFD, 0xEC, 0x83, 0xFF}}},
	{{{-70, -48, -8},0, {290, -652},{0xFD, 0xEC, 0x83, 0xFF}}},
	{{{-70, -46, -8},0, {290, -656},{0xFD, 0xEC, 0x83, 0xFF}}},
	{{{-64, 50, -7},0, {1772, -670},{0xF5, 0x46, 0x96, 0xFF}}},
	{{{-64, 49, -8},0, {1772, -661},{0xF5, 0x46, 0x96, 0xFF}}},
	{{{-70, 48, -8},0, {1790, -661},{0xF5, 0x46, 0x96, 0xFF}}},
	{{{-70, 49, -7},0, {1790, -670},{0xF5, 0x46, 0x96, 0xFF}}},
	{{{-64, 49, -8},0, {1292, -414},{0xFD, 0x14, 0x83, 0xFF}}},
	{{{-64, 47, -8},0, {1296, -414},{0xFD, 0x14, 0x83, 0xFF}}},
	{{{-70, 46, -8},0, {1296, -405},{0xFD, 0x14, 0x83, 0xFF}}},
	{{{-70, 48, -8},0, {1287, -405},{0xFD, 0x14, 0x83, 0xFF}}},
	{{{-64, 43, -8},0, {1260, -414},{0xFD, 0x5, 0x81, 0xFF}}},
	{{{-70, 43, -8},0, {1260, -405},{0xFD, 0x5, 0x81, 0xFF}}},
	{{{-70, 46, -8},0, {1278, -405},{0xFD, 0x5, 0x81, 0xFF}}},
	{{{-64, 47, -8},0, {1278, -414},{0xFD, 0x5, 0x81, 0xFF}}},
	{{{-70, 43, -8},0, {1260, -405},{0xF3, 0x5, 0x82, 0xFF}}},
	{{{-74, 43, -8},0, {1260, -396},{0xF3, 0x5, 0x82, 0xFF}}},
	{{{-72, 46, -8},0, {1278, -396},{0xF3, 0x5, 0x82, 0xFF}}},
	{{{-70, 46, -8},0, {1278, -405},{0xF3, 0x5, 0x82, 0xFF}}},
	{{{-75, 43, -7},0, {1260, -378},{0xCD, 0x13, 0x8D, 0xFF}}},
	{{{-74, 47, -7},0, {1278, -378},{0xCD, 0x13, 0x8D, 0xFF}}},
	{{{-72, 46, -8},0, {1278, -387},{0xCD, 0x13, 0x8D, 0xFF}}},
	{{{-74, 43, -8},0, {1260, -387},{0xCD, 0x13, 0x8D, 0xFF}}},
	{{{-74, 47, -7},0, {1278, -378},{0xD8, 0x3D, 0x98, 0xFF}}},
	{{{-70, 49, -7},0, {1296, -378},{0xD8, 0x3D, 0x98, 0xFF}}},
	{{{-70, 48, -8},0, {1296, -387},{0xD8, 0x3D, 0x98, 0xFF}}},
	{{{-72, 46, -8},0, {1278, -387},{0xD8, 0x3D, 0x98, 0xFF}}},
	{{{64, -50, 7},0, {748, -890},{0xB, 0xBA, 0x6A, 0xFF}}},
	{{{70, -49, 7},0, {766, -890},{0xB, 0xBA, 0x6A, 0xFF}}},
	{{{70, -48, 8},0, {766, -899},{0xB, 0xBA, 0x6A, 0xFF}}},
	{{{64, -49, 8},0, {748, -899},{0xB, 0xBA, 0x6A, 0xFF}}},
	{{{70, -49, 7},0, {766, -890},{0x28, 0xC3, 0x68, 0xFF}}},
	{{{74, -47, 7},0, {784, -890},{0x28, 0xC3, 0x68, 0xFF}}},
	{{{72, -46, 8},0, {784, -899},{0x28, 0xC3, 0x68, 0xFF}}},
	{{{70, -48, 8},0, {766, -899},{0x28, 0xC3, 0x68, 0xFF}}},
	{{{75, -43, 7},0, {820, -890},{0x33, 0xED, 0x73, 0xFF}}},
	{{{74, -43, 8},0, {820, -899},{0x33, 0xED, 0x73, 0xFF}}},
	{{{72, -46, 8},0, {802, -899},{0x33, 0xED, 0x73, 0xFF}}},
	{{{74, -47, 7},0, {802, -890},{0x33, 0xED, 0x73, 0xFF}}},
	{{{74, -43, 8},0, {820, -899},{0xD, 0xFB, 0x7E, 0xFF}}},
	{{{70, -43, 8},0, {820, -908},{0xD, 0xFB, 0x7E, 0xFF}}},
	{{{70, -46, 8},0, {802, -908},{0xD, 0xFB, 0x7E, 0xFF}}},
	{{{72, -46, 8},0, {802, -899},{0xD, 0xFB, 0x7E, 0xFF}}},
	{{{64, -43, 8},0, {820, -926},{0x3, 0xFB, 0x7F, 0xFF}}},
	{{{64, -47, 8},0, {802, -926},{0x3, 0xFB, 0x7F, 0xFF}}},
	{{{70, -46, 8},0, {802, -917},{0x3, 0xFB, 0x7F, 0xFF}}},
	{{{70, -43, 8},0, {820, -917},{0x3, 0xFB, 0x7F, 0xFF}}},
	{{{64, -47, 8},0, {748, -906},{0x3, 0xEC, 0x7D, 0xFF}}},
	{{{64, -49, 8},0, {748, -908},{0x3, 0xEC, 0x7D, 0xFF}}},
	{{{70, -48, 8},0, {766, -908},{0x3, 0xEC, 0x7D, 0xFF}}},
	{{{70, -46, 8},0, {766, -904},{0x3, 0xEC, 0x7D, 0xFF}}},
	{{{64, 50, 7},0, {1332, -890},{0xB, 0x46, 0x6A, 0xFF}}},
	{{{64, 49, 8},0, {1332, -899},{0xB, 0x46, 0x6A, 0xFF}}},
	{{{70, 48, 8},0, {1314, -899},{0xB, 0x46, 0x6A, 0xFF}}},
	{{{70, 49, 7},0, {1314, -890},{0xB, 0x46, 0x6A, 0xFF}}},
	{{{64, 49, 8},0, {1292, -926},{0x3, 0x14, 0x7D, 0xFF}}},
	{{{64, 47, 8},0, {1296, -926},{0x3, 0x14, 0x7D, 0xFF}}},
	{{{70, 46, 8},0, {1296, -917},{0x3, 0x14, 0x7D, 0xFF}}},
	{{{70, 48, 8},0, {1287, -917},{0x3, 0x14, 0x7D, 0xFF}}},
	{{{64, 43, 8},0, {1260, -926},{0x3, 0x5, 0x7F, 0xFF}}},
	{{{70, 43, 8},0, {1260, -917},{0x3, 0x5, 0x7F, 0xFF}}},
	{{{70, 46, 8},0, {1278, -917},{0x3, 0x5, 0x7F, 0xFF}}},
	{{{64, 47, 8},0, {1278, -926},{0x3, 0x5, 0x7F, 0xFF}}},
	{{{70, 43, 8},0, {1260, -917},{0xD, 0x5, 0x7E, 0xFF}}},
	{{{74, 43, 8},0, {1260, -908},{0xD, 0x5, 0x7E, 0xFF}}},
	{{{72, 46, 8},0, {1278, -908},{0xD, 0x5, 0x7E, 0xFF}}},
	{{{70, 46, 8},0, {1278, -917},{0xD, 0x5, 0x7E, 0xFF}}},
	{{{75, 43, 7},0, {1260, -890},{0x33, 0x13, 0x73, 0xFF}}},
	{{{74, 47, 7},0, {1278, -890},{0x33, 0x13, 0x73, 0xFF}}},
	{{{72, 46, 8},0, {1278, -899},{0x33, 0x13, 0x73, 0xFF}}},
	{{{74, 43, 8},0, {1260, -899},{0x33, 0x13, 0x73, 0xFF}}},
	{{{74, 47, 7},0, {1278, -890},{0x28, 0x3D, 0x68, 0xFF}}},
	{{{70, 49, 7},0, {1296, -890},{0x28, 0x3D, 0x68, 0xFF}}},
	{{{70, 48, 8},0, {1296, -899},{0x28, 0x3D, 0x68, 0xFF}}},
	{{{72, 46, 8},0, {1278, -899},{0x28, 0x3D, 0x68, 0xFF}}},
	{{{64, -50, -7},0, {748, -670},{0xB, 0xBA, 0x96, 0xFF}}},
	{{{64, -49, -8},0, {748, -661},{0xB, 0xBA, 0x96, 0xFF}}},
	{{{70, -48, -8},0, {766, -661},{0xB, 0xBA, 0x96, 0xFF}}},
	{{{70, -49, -7},0, {766, -670},{0xB, 0xBA, 0x96, 0xFF}}},
	{{{64, -49, -8},0, {748, -661},{0x3, 0xEC, 0x83, 0xFF}}},
	{{{64, -47, -8},0, {748, -652},{0x3, 0xEC, 0x83, 0xFF}}},
	{{{70, -46, -8},0, {766, -652},{0x3, 0xEC, 0x83, 0xFF}}},
	{{{70, -48, -8},0, {766, -661},{0x3, 0xEC, 0x83, 0xFF}}},
	{{{64, -43, -8},0, {820, -634},{0x3, 0xFB, 0x81, 0xFF}}},
	{{{70, -43, -8},0, {820, -643},{0x3, 0xFB, 0x81, 0xFF}}},
	{{{70, -46, -8},0, {802, -643},{0x3, 0xFB, 0x81, 0xFF}}},
	{{{64, -47, -8},0, {802, -634},{0x3, 0xFB, 0x81, 0xFF}}},
	{{{70, -43, -8},0, {820, -643},{0xD, 0xFB, 0x82, 0xFF}}},
	{{{74, -43, -8},0, {820, -652},{0xD, 0xFB, 0x82, 0xFF}}},
	{{{72, -46, -8},0, {802, -652},{0xD, 0xFB, 0x82, 0xFF}}},
	{{{70, -46, -8},0, {802, -643},{0xD, 0xFB, 0x82, 0xFF}}},
	{{{75, -43, -7},0, {820, -670},{0x33, 0xED, 0x8D, 0xFF}}},
	{{{74, -47, -7},0, {802, -670},{0x33, 0xED, 0x8D, 0xFF}}},
	{{{72, -46, -8},0, {802, -661},{0x33, 0xED, 0x8D, 0xFF}}},
	{{{74, -43, -8},0, {820, -661},{0x33, 0xED, 0x8D, 0xFF}}},
	{{{74, -47, -7},0, {802, -670},{0x28, 0xC3, 0x98, 0xFF}}},
	{{{70, -49, -7},0, {784, -670},{0x28, 0xC3, 0x98, 0xFF}}},
	{{{70, -48, -8},0, {784, -661},{0x28, 0xC3, 0x98, 0xFF}}},
	{{{72, -46, -8},0, {802, -661},{0x28, 0xC3, 0x98, 0xFF}}},
	{{{64, 50, -7},0, {1332, -670},{0xB, 0x46, 0x96, 0xFF}}},
	{{{70, 49, -7},0, {1314, -670},{0xB, 0x46, 0x96, 0xFF}}},
	{{{70, 48, -8},0, {1314, -661},{0xB, 0x46, 0x96, 0xFF}}},
	{{{64, 49, -8},0, {1332, -661},{0xB, 0x46, 0x96, 0xFF}}},
	{{{70, 49, -7},0, {1314, -670},{0x28, 0x3D, 0x98, 0xFF}}},
	{{{74, 47, -7},0, {1296, -670},{0x28, 0x3D, 0x98, 0xFF}}},
	{{{72, 46, -8},0, {1296, -661},{0x28, 0x3D, 0x98, 0xFF}}},
	{{{70, 48, -8},0, {1314, -661},{0x28, 0x3D, 0x98, 0xFF}}},
	{{{75, 43, -7},0, {1260, -670},{0x33, 0x13, 0x8D, 0xFF}}},
	{{{74, 43, -8},0, {1260, -661},{0x33, 0x13, 0x8D, 0xFF}}},
	{{{72, 46, -8},0, {1278, -661},{0x33, 0x13, 0x8D, 0xFF}}},
	{{{74, 47, -7},0, {1278, -670},{0x33, 0x13, 0x8D, 0xFF}}},
	{{{74, 43, -8},0, {1260, -661},{0xD, 0x5, 0x82, 0xFF}}},
	{{{70, 43, -8},0, {1260, -652},{0xD, 0x5, 0x82, 0xFF}}},
	{{{70, 46, -8},0, {1278, -652},{0xD, 0x5, 0x82, 0xFF}}},
	{{{72, 46, -8},0, {1278, -661},{0xD, 0x5, 0x82, 0xFF}}},
	{{{64, 43, -8},0, {1260, -634},{0x3, 0x5, 0x81, 0xFF}}},
	{{{64, 47, -8},0, {1278, -634},{0x3, 0x5, 0x81, 0xFF}}},
	{{{70, 46, -8},0, {1278, -643},{0x3, 0x5, 0x81, 0xFF}}},
	{{{70, 43, -8},0, {1260, -643},{0x3, 0x5, 0x81, 0xFF}}},
	{{{64, 47, -8},0, {1278, -634},{0x3, 0x14, 0x83, 0xFF}}},
	{{{64, 49, -8},0, {1296, -634},{0x3, 0x14, 0x83, 0xFF}}},
	{{{70, 48, -8},0, {1296, -643},{0x3, 0x14, 0x83, 0xFF}}},
	{{{70, 46, -8},0, {1278, -643},{0x3, 0x14, 0x83, 0xFF}}},
	{{{-64, -50, -7},0, {308, -670},{0xEC, 0x83, 0x0, 0xFF}}},
	{{{-64, -50, 7},0, {308, -890},{0xEC, 0x83, 0x0, 0xFF}}},
	{{{-70, -49, 7},0, {290, -890},{0xEC, 0x83, 0x0, 0xFF}}},
	{{{-70, -49, -7},0, {290, -670},{0xEC, 0x83, 0x0, 0xFF}}},
	{{{-70, -49, -7},0, {290, -670},{0xB9, 0x96, 0x0, 0xFF}}},
	{{{-70, -49, 7},0, {290, -890},{0xB9, 0x96, 0x0, 0xFF}}},
	{{{-74, -47, 7},0, {272, -890},{0xB9, 0x96, 0x0, 0xFF}}},
	{{{-74, -47, -7},0, {272, -670},{0xB9, 0x96, 0x0, 0xFF}}},
	{{{-74, -47, -7},0, {802, -378},{0x88, 0xD5, 0x0, 0xFF}}},
	{{{-74, -47, 7},0, {802, -158},{0x88, 0xD5, 0x0, 0xFF}}},
	{{{-75, -43, 7},0, {820, -158},{0x88, 0xD5, 0x0, 0xFF}}},
	{{{-75, -43, -7},0, {820, -378},{0x88, 0xD5, 0x0, 0xFF}}},
	{{{-64, -43, 8},0, {820, -1146},{0xFD, 0x0, 0x7F, 0xFF}}},
	{{{-64, 43, 8},0, {1260, -1146},{0xFD, 0x0, 0x7F, 0xFF}}},
	{{{-70, 43, 8},0, {1260, -1155},{0xFD, 0x0, 0x7F, 0xFF}}},
	{{{-70, -43, 8},0, {820, -1155},{0xFD, 0x0, 0x7F, 0xFF}}},
	{{{-70, -43, 8},0, {820, -140},{0xF3, 0x0, 0x7E, 0xFF}}},
	{{{-70, 43, 8},0, {1260, -140},{0xF3, 0x0, 0x7E, 0xFF}}},
	{{{-74, 43, 8},0, {1260, -149},{0xF3, 0x0, 0x7E, 0xFF}}},
	{{{-74, -43, 8},0, {820, -149},{0xF3, 0x0, 0x7E, 0xFF}}},
	{{{-75, -43, 7},0, {820, -158},{0xCB, 0x0, 0x74, 0xFF}}},
	{{{-74, -43, 8},0, {820, -149},{0xCB, 0x0, 0x74, 0xFF}}},
	{{{-74, 43, 8},0, {1260, -149},{0xCB, 0x0, 0x74, 0xFF}}},
	{{{-75, 10, 7},0, {1091, -158},{0xCB, 0x0, 0x74, 0xFF}}},
	{{{-75, 43, 7},0, {1260, -158},{0xCB, 0x0, 0x74, 0xFF}}},
	{{{-75, -9, 7},0, {992, -158},{0xCB, 0x0, 0x74, 0xFF}}},
	{{{-64, 50, 7},0, {1772, -890},{0xEC, 0x7D, 0x0, 0xFF}}},
	{{{-64, 50, -7},0, {1772, -670},{0xEC, 0x7D, 0x0, 0xFF}}},
	{{{-70, 49, -7},0, {1790, -670},{0xEC, 0x7D, 0x0, 0xFF}}},
	{{{-70, 49, 7},0, {1790, -890},{0xEC, 0x7D, 0x0, 0xFF}}},
	{{{-70, 49, 7},0, {1296, -158},{0xB9, 0x6A, 0x0, 0xFF}}},
	{{{-70, 49, -7},0, {1296, -378},{0xB9, 0x6A, 0x0, 0xFF}}},
	{{{-74, 47, -7},0, {1278, -378},{0xB9, 0x6A, 0x0, 0xFF}}},
	{{{-74, 47, 7},0, {1278, -158},{0xB9, 0x6A, 0x0, 0xFF}}},
	{{{-74, 47, 7},0, {1278, -158},{0x88, 0x2B, 0x0, 0xFF}}},
	{{{-74, 47, -7},0, {1278, -378},{0x88, 0x2B, 0x0, 0xFF}}},
	{{{-75, 43, -7},0, {1260, -378},{0x88, 0x2B, 0x0, 0xFF}}},
	{{{-75, 43, 7},0, {1260, -158},{0x88, 0x2B, 0x0, 0xFF}}},
	{{{-64, 43, -8},0, {1260, -414},{0xFD, 0x0, 0x81, 0xFF}}},
	{{{-64, -43, -8},0, {820, -414},{0xFD, 0x0, 0x81, 0xFF}}},
	{{{-70, -43, -8},0, {820, -405},{0xFD, 0x0, 0x81, 0xFF}}},
	{{{-70, 43, -8},0, {1260, -405},{0xFD, 0x0, 0x81, 0xFF}}},
	{{{-70, 43, -8},0, {1260, -405},{0xF3, 0x0, 0x82, 0xFF}}},
	{{{-70, -43, -8},0, {820, -405},{0xF3, 0x0, 0x82, 0xFF}}},
	{{{-74, -43, -8},0, {820, -387},{0xF3, 0x0, 0x82, 0xFF}}},
	{{{-74, 43, -8},0, {1260, -387},{0xF3, 0x0, 0x82, 0xFF}}},
	{{{-75, 43, -7},0, {1260, -378},{0xCB, 0x0, 0x8C, 0xFF}}},
	{{{-74, 43, -8},0, {1260, -387},{0xCB, 0x0, 0x8C, 0xFF}}},
	{{{-74, -43, -8},0, {820, -387},{0xCB, 0x0, 0x8C, 0xFF}}},
	{{{-75, -9, -7},0, {992, -378},{0xCB, 0x0, 0x8C, 0xFF}}},
	{{{-75, -43, -7},0, {820, -378},{0xCB, 0x0, 0x8C, 0xFF}}},
	{{{-75, 10, -7},0, {1091, -378},{0xCB, 0x0, 0x8C, 0xFF}}},
	{{{64, -50, -7},0, {748, -670},{0x0, 0xB8, 0x97, 0xFF}}},
	{{{-64, -50, -7},0, {308, -670},{0x0, 0xB8, 0x97, 0xFF}}},
	{{{-64, -49, -8},0, {308, -661},{0x0, 0xB8, 0x97, 0xFF}}},
	{{{64, -49, -8},0, {748, -661},{0x0, 0xB8, 0x97, 0xFF}}},
	{{{64, -49, -8},0, {748, -661},{0x0, 0xEC, 0x83, 0xFF}}},
	{{{-64, -49, -8},0, {308, -661},{0x0, 0xEC, 0x83, 0xFF}}},
	{{{-64, -47, -8},0, {308, -652},{0x0, 0xEC, 0x83, 0xFF}}},
	{{{64, -47, -8},0, {748, -652},{0x0, 0xEC, 0x83, 0xFF}}},
	{{{64, -47, -8},0, {802, -634},{0x0, 0xFB, 0x81, 0xFF}}},
	{{{-64, -47, -8},0, {802, -414},{0x0, 0xFB, 0x81, 0xFF}}},
	{{{-64, -43, -8},0, {820, -414},{0x0, 0xFB, 0x81, 0xFF}}},
	{{{64, -43, -8},0, {820, -634},{0x0, 0xFB, 0x81, 0xFF}}},
	{{{-64, 50, -7},0, {1772, -670},{0x0, 0x48, 0x97, 0xFF}}},
	{{{64, 50, -7},0, {1332, -670},{0x0, 0x48, 0x97, 0xFF}}},
	{{{64, 49, -8},0, {1332, -661},{0x0, 0x48, 0x97, 0xFF}}},
	{{{-64, 49, -8},0, {1772, -661},{0x0, 0x48, 0x97, 0xFF}}},
	{{{-64, 49, -8},0, {1296, -414},{0x0, 0x14, 0x83, 0xFF}}},
	{{{64, 49, -8},0, {1296, -634},{0x0, 0x14, 0x83, 0xFF}}},
	{{{64, 47, -8},0, {1278, -634},{0x0, 0x14, 0x83, 0xFF}}},
	{{{-64, 47, -8},0, {1278, -414},{0x0, 0x14, 0x83, 0xFF}}},
	{{{-64, 47, -8},0, {1278, -414},{0x0, 0x5, 0x81, 0xFF}}},
	{{{64, 47, -8},0, {1278, -634},{0x0, 0x5, 0x81, 0xFF}}},
	{{{64, 43, -8},0, {1260, -634},{0x0, 0x5, 0x81, 0xFF}}},
	{{{-64, 43, -8},0, {1260, -414},{0x0, 0x5, 0x81, 0xFF}}},
	{{{75, 43, -7},0, {1260, -670},{0x35, 0x0, 0x8C, 0xFF}}},
	{{{75, -43, -7},0, {820, -670},{0x35, 0x0, 0x8C, 0xFF}}},
	{{{74, -43, -8},0, {820, -661},{0x35, 0x0, 0x8C, 0xFF}}},
	{{{74, 43, -8},0, {1260, -661},{0x35, 0x0, 0x8C, 0xFF}}},
	{{{74, 43, -8},0, {1260, -661},{0xD, 0x0, 0x82, 0xFF}}},
	{{{74, -43, -8},0, {820, -661},{0xD, 0x0, 0x82, 0xFF}}},
	{{{70, -43, -8},0, {820, -643},{0xD, 0x0, 0x82, 0xFF}}},
	{{{70, 43, -8},0, {1260, -643},{0xD, 0x0, 0x82, 0xFF}}},
	{{{70, 43, -8},0, {1260, -643},{0x3, 0x0, 0x81, 0xFF}}},
	{{{70, -43, -8},0, {820, -643},{0x3, 0x0, 0x81, 0xFF}}},
	{{{64, -43, -8},0, {820, -634},{0x3, 0x0, 0x81, 0xFF}}},
	{{{64, 43, -8},0, {1260, -634},{0x3, 0x0, 0x81, 0xFF}}},
	{{{64, -50, 7},0, {748, -890},{0x14, 0x83, 0x0, 0xFF}}},
	{{{64, -50, -7},0, {748, -670},{0x14, 0x83, 0x0, 0xFF}}},
	{{{70, -49, -7},0, {766, -670},{0x14, 0x83, 0x0, 0xFF}}},
	{{{70, -49, 7},0, {766, -890},{0x14, 0x83, 0x0, 0xFF}}},
	{{{70, -49, 7},0, {766, -890},{0x47, 0x96, 0x0, 0xFF}}},
	{{{70, -49, -7},0, {766, -670},{0x47, 0x96, 0x0, 0xFF}}},
	{{{74, -47, -7},0, {802, -670},{0x47, 0x96, 0x0, 0xFF}}},
	{{{74, -47, 7},0, {802, -890},{0x47, 0x96, 0x0, 0xFF}}},
	{{{74, -47, 7},0, {802, -890},{0x78, 0xD5, 0x0, 0xFF}}},
	{{{74, -47, -7},0, {802, -670},{0x78, 0xD5, 0x0, 0xFF}}},
	{{{75, -43, -7},0, {820, -670},{0x78, 0xD5, 0x0, 0xFF}}},
	{{{75, -43, 7},0, {820, -890},{0x78, 0xD5, 0x0, 0xFF}}},
	{{{64, 50, -7},0, {1332, -670},{0x14, 0x7D, 0x0, 0xFF}}},
	{{{64, 50, 7},0, {1332, -890},{0x14, 0x7D, 0x0, 0xFF}}},
	{{{70, 49, 7},0, {1314, -890},{0x14, 0x7D, 0x0, 0xFF}}},
	{{{70, 49, -7},0, {1314, -670},{0x14, 0x7D, 0x0, 0xFF}}},
	{{{70, 49, -7},0, {1314, -670},{0x47, 0x6A, 0x0, 0xFF}}},
	{{{70, 49, 7},0, {1314, -890},{0x47, 0x6A, 0x0, 0xFF}}},
	{{{74, 47, 7},0, {1278, -890},{0x47, 0x6A, 0x0, 0xFF}}},
	{{{74, 47, -7},0, {1278, -670},{0x47, 0x6A, 0x0, 0xFF}}},
	{{{74, 47, -7},0, {1278, -670},{0x78, 0x2B, 0x0, 0xFF}}},
	{{{74, 47, 7},0, {1278, -890},{0x78, 0x2B, 0x0, 0xFF}}},
	{{{75, 43, 7},0, {1260, -890},{0x78, 0x2B, 0x0, 0xFF}}},
	{{{75, 43, -7},0, {1260, -670},{0x78, 0x2B, 0x0, 0xFF}}},
	{{{64, 43, 8},0, {1260, -926},{0x3, 0x0, 0x7F, 0xFF}}},
	{{{64, -43, 8},0, {820, -926},{0x3, 0x0, 0x7F, 0xFF}}},
	{{{70, -43, 8},0, {820, -917},{0x3, 0x0, 0x7F, 0xFF}}},
	{{{70, 43, 8},0, {1260, -917},{0x3, 0x0, 0x7F, 0xFF}}},
	{{{70, 43, 8},0, {1260, -917},{0xD, 0x0, 0x7E, 0xFF}}},
	{{{70, -43, 8},0, {820, -917},{0xD, 0x0, 0x7E, 0xFF}}},
	{{{74, -43, 8},0, {820, -899},{0xD, 0x0, 0x7E, 0xFF}}},
	{{{74, 43, 8},0, {1260, -899},{0xD, 0x0, 0x7E, 0xFF}}},
	{{{74, 43, 8},0, {1260, -899},{0x35, 0x0, 0x74, 0xFF}}},
	{{{74, -43, 8},0, {820, -899},{0x35, 0x0, 0x74, 0xFF}}},
	{{{75, -43, 7},0, {820, -890},{0x35, 0x0, 0x74, 0xFF}}},
	{{{75, 43, 7},0, {1260, -890},{0x35, 0x0, 0x74, 0xFF}}},
	{{{-64, -50, 7},0, {308, -890},{0x0, 0xB8, 0x69, 0xFF}}},
	{{{64, -50, 7},0, {748, -890},{0x0, 0xB8, 0x69, 0xFF}}},
	{{{64, -49, 8},0, {748, -899},{0x0, 0xB8, 0x69, 0xFF}}},
	{{{-64, -49, 8},0, {308, -899},{0x0, 0xB8, 0x69, 0xFF}}},
	{{{-64, -49, 8},0, {308, -899},{0x0, 0xEC, 0x7D, 0xFF}}},
	{{{64, -49, 8},0, {748, -899},{0x0, 0xEC, 0x7D, 0xFF}}},
	{{{64, -47, 8},0, {748, -908},{0x0, 0xEC, 0x7D, 0xFF}}},
	{{{-64, -47, 8},0, {308, -908},{0x0, 0xEC, 0x7D, 0xFF}}},
	{{{-64, -47, 8},0, {802, -1146},{0x0, 0xFB, 0x7F, 0xFF}}},
	{{{64, -47, 8},0, {802, -926},{0x0, 0xFB, 0x7F, 0xFF}}},
	{{{64, -43, 8},0, {820, -926},{0x0, 0xFB, 0x7F, 0xFF}}},
	{{{-64, -43, 8},0, {820, -1146},{0x0, 0xFB, 0x7F, 0xFF}}},
	{{{64, 50, 7},0, {1332, -890},{0x0, 0x48, 0x69, 0xFF}}},
	{{{-64, 50, 7},0, {1772, -890},{0x0, 0x48, 0x69, 0xFF}}},
	{{{-64, 49, 8},0, {1772, -899},{0x0, 0x48, 0x69, 0xFF}}},
	{{{64, 49, 8},0, {1332, -899},{0x0, 0x48, 0x69, 0xFF}}},
	{{{64, 49, 8},0, {1296, -926},{0x0, 0x14, 0x7D, 0xFF}}},
	{{{-64, 49, 8},0, {1296, -1146},{0x0, 0x14, 0x7D, 0xFF}}},
	{{{-64, 47, 8},0, {1278, -1146},{0x0, 0x14, 0x7D, 0xFF}}},
	{{{64, 47, 8},0, {1278, -926},{0x0, 0x14, 0x7D, 0xFF}}},
	{{{64, 47, 8},0, {1278, -926},{0x0, 0x5, 0x7F, 0xFF}}},
	{{{-64, 47, 8},0, {1278, -1146},{0x0, 0x5, 0x7F, 0xFF}}},
	{{{-64, 43, 8},0, {1260, -1146},{0x0, 0x5, 0x7F, 0xFF}}},
	{{{64, 43, 8},0, {1260, -926},{0x0, 0x5, 0x7F, 0xFF}}},
	{{{-64, -50, -7},0, {308, -670},{0x0, 0x81, 0x0, 0xFF}}},
	{{{64, -50, -7},0, {748, -670},{0x0, 0x81, 0x0, 0xFF}}},
	{{{64, -50, 7},0, {748, -890},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-64, -50, 7},0, {308, -890},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-75, 10, -7},0, {1091, -378},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-75, 10, 7},0, {1091, -158},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-75, 43, 7},0, {1260, -158},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-75, 43, -7},0, {1260, -378},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-75, -9, 7},0, {992, -158},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-75, 10, 7},0, {1091, -158},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-230, 10, 7},0, {1091, -158},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-230, -9, 7},0, {992, -158},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-75, 10, -7},0, {1091, -378},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-75, -9, -7},0, {992, -378},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-230, -9, -7},0, {992, -378},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-230, 10, -7},0, {1091, -378},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-75, -9, -7},0, {992, -378},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-75, -9, 7},0, {992, -158},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-230, -9, 7},0, {992, -158},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-230, -9, -7},0, {992, -378},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-75, 10, 7},0, {1091, -158},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-75, 10, -7},0, {1091, -378},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-230, 10, -7},0, {1091, -378},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-230, 10, 7},0, {1091, -158},{0x0, 0x7F, 0x0, 0xFF}}},
};
gtTriN SignP2_2_tris_0[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {3, 4, 5, 0},
    {6, 7, 8, 0}, {9, 10, 11, 0},
    {12, 13, 14, 0}, {15, 16, 17, 0},
    {18, 19, 20, 0}, {21, 22, 23, 0},
    {24, 25, 26, 0}, {24, 26, 27, 0},
    {28, 29, 30, 0}, {28, 30, 31, 0},
    {32, 33, 34, 0}, {32, 34, 35, 0},
    {36, 37, 38, 0}, {36, 38, 39, 0},
    {40, 41, 42, 0}, {40, 42, 43, 0},
    {44, 45, 46, 0}, {44, 46, 47, 0},
    {48, 49, 50, 0}, {48, 50, 51, 0},
    {52, 53, 54, 0}, {52, 54, 55, 0},
    {56, 57, 58, 0}, {56, 58, 59, 0},
    {60, 61, 62, 0}, {60, 62, 63, 0},
// 28
};
gtTriN SignP2_2_tris_1[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {0, 2, 3, 0},
    {4, 5, 6, 0}, {4, 6, 7, 0},
    {8, 9, 10, 0}, {8, 10, 11, 0},
    {12, 13, 14, 0}, {12, 14, 15, 0},
    {16, 17, 18, 0}, {16, 18, 19, 0},
    {20, 21, 22, 0}, {20, 22, 23, 0},
    {24, 25, 26, 0}, {24, 26, 27, 0},
    {28, 29, 30, 0}, {28, 30, 31, 0},
    {32, 33, 34, 0}, {32, 34, 35, 0},
    {36, 37, 38, 0}, {36, 38, 39, 0},
    {40, 41, 42, 0}, {40, 42, 43, 0},
    {44, 45, 46, 0}, {44, 46, 47, 0},
    {48, 49, 50, 0}, {48, 50, 51, 0},
    {52, 53, 54, 0}, {52, 54, 55, 0},
    {56, 57, 58, 0}, {56, 58, 59, 0},
    {60, 61, 62, 0}, {60, 62, 63, 0},
// 32
};
gtTriN SignP2_2_tris_2[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {0, 2, 3, 0},
    {4, 5, 6, 0}, {4, 6, 7, 0},
    {8, 9, 10, 0}, {8, 10, 11, 0},
    {12, 13, 14, 0}, {12, 14, 15, 0},
    {16, 17, 18, 0}, {16, 18, 19, 0},
    {20, 21, 22, 0}, {20, 22, 23, 0},
    {24, 25, 26, 0}, {24, 26, 27, 0},
    {28, 29, 30, 0}, {28, 30, 31, 0},
    {32, 33, 34, 0}, {32, 34, 35, 0},
    {36, 37, 38, 0}, {36, 38, 39, 0},
    {40, 41, 42, 0}, {40, 42, 43, 0},
    {44, 45, 46, 0}, {44, 46, 47, 0},
    {48, 49, 50, 0}, {48, 50, 51, 0},
    {52, 53, 54, 0}, {52, 54, 55, 0},
    {56, 57, 58, 0}, {56, 58, 59, 0},
    {60, 61, 62, 0}, {60, 62, 63, 0},
// 32
};
gtTriN SignP2_2_tris_3[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {0, 2, 3, 0},
    {4, 5, 6, 0}, {4, 6, 7, 0},
    {8, 9, 10, 0}, {8, 10, 11, 0},
    {12, 13, 14, 0}, {12, 14, 15, 0},
    {16, 17, 18, 0}, {16, 18, 19, 0},
    {20, 21, 22, 0}, {20, 22, 23, 0},
    {24, 25, 26, 0}, {24, 26, 27, 0},
    {28, 29, 30, 0}, {28, 30, 31, 0},
    {32, 33, 34, 0}, {32, 34, 35, 0},
    {36, 37, 38, 0}, {36, 38, 39, 0},
    {40, 41, 42, 0}, {40, 42, 43, 0},
    {44, 45, 46, 0}, {44, 46, 47, 0},
    {48, 49, 50, 0}, {48, 50, 51, 0},
    {52, 53, 54, 0}, {52, 54, 55, 0},
    {56, 57, 58, 0}, {56, 58, 59, 0},
    {60, 61, 62, 0}, {60, 62, 63, 0},
// 32
};
gtTriN SignP2_2_tris_4[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {0, 2, 3, 0},
    {4, 5, 6, 0}, {6, 7, 4, 0},
    {6, 8, 7, 0}, {7, 9, 4, 0},
    {10, 11, 12, 0}, {10, 12, 13, 0},
    {14, 15, 16, 0}, {14, 16, 17, 0},
    {18, 19, 20, 0}, {18, 20, 21, 0},
    {22, 23, 24, 0}, {22, 24, 25, 0},
    {26, 27, 28, 0}, {26, 28, 29, 0},
    {30, 31, 32, 0}, {32, 33, 30, 0},
    {32, 34, 33, 0}, {33, 35, 30, 0},
    {36, 37, 38, 0}, {36, 38, 39, 0},
    {40, 41, 42, 0}, {40, 42, 43, 0},
    {44, 45, 46, 0}, {44, 46, 47, 0},
    {48, 49, 50, 0}, {48, 50, 51, 0},
    {52, 53, 54, 0}, {52, 54, 55, 0},
    {56, 57, 58, 0}, {56, 58, 59, 0},
    {60, 61, 62, 0}, {60, 62, 63, 0},
// 34
};
gtTriN SignP2_2_tris_5[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {0, 2, 3, 0},
    {4, 5, 6, 0}, {4, 6, 7, 0},
    {8, 9, 10, 0}, {8, 10, 11, 0},
    {12, 13, 14, 0}, {12, 14, 15, 0},
    {16, 17, 18, 0}, {16, 18, 19, 0},
    {20, 21, 22, 0}, {20, 22, 23, 0},
    {24, 25, 26, 0}, {24, 26, 27, 0},
    {28, 29, 30, 0}, {28, 30, 31, 0},
    {32, 33, 34, 0}, {32, 34, 35, 0},
    {36, 37, 38, 0}, {36, 38, 39, 0},
    {40, 41, 42, 0}, {40, 42, 43, 0},
    {44, 45, 46, 0}, {44, 46, 47, 0},
    {48, 49, 50, 0}, {48, 50, 51, 0},
    {52, 53, 54, 0}, {52, 54, 55, 0},
    {56, 57, 58, 0}, {56, 58, 59, 0},
    {60, 61, 62, 0}, {60, 62, 63, 0},
// 32
};
gtTriN SignP2_2_tris_6[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {0, 2, 3, 0},
    {4, 5, 6, 0}, {4, 6, 7, 0},
    {8, 9, 10, 0}, {8, 10, 11, 0},
    {12, 13, 14, 0}, {12, 14, 15, 0},
    {16, 17, 18, 0}, {16, 18, 19, 0},
    {20, 21, 22, 0}, {20, 22, 23, 0},
    {24, 25, 26, 0}, {24, 26, 27, 0},
};
gtState SignP2_2_State = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    64, // vtxCount  8
    0, // vtxV0 9
    28, // triCount a
    0x0, // some_flag b
    NULL, // c
    gsDPSetOtherMode(
        G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
        G_AC_NONE | G_ZS_PIXEL
    ), // 10
    {
    // integer portion:
        0x00010000, 0x00000000,
        0x00000001, 0x00000000,
        0x00000000, 0x00010000,
        0x00000000, 0x00000001,
    // fractional portion:
        0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000000, 0x00000000,
    }
};


gtStateL SignP2_2_StateL_0 = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    64, // vtxCount  8
    0, // vtxV0 9
    32, // triCount a
    GT_FLAG_NOMTX, // some_flag b
    NULL, // c
    gsDPNoOp(), // 10
};


gtStateL SignP2_2_StateL_1 = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    64, // vtxCount  8
    0, // vtxV0 9
    32, // triCount a
    GT_FLAG_NOMTX, // some_flag b
    NULL, // c
    gsDPNoOp(), // 10
};


gtStateL SignP2_2_StateL_2 = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    64, // vtxCount  8
    0, // vtxV0 9
    32, // triCount a
    GT_FLAG_NOMTX, // some_flag b
    NULL, // c
    gsDPNoOp(), // 10
};


gtStateL SignP2_2_StateL_3 = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    64, // vtxCount  8
    0, // vtxV0 9
    34, // triCount a
    GT_FLAG_NOMTX, // some_flag b
    NULL, // c
    gsDPNoOp(), // 10
};


gtStateL SignP2_2_StateL_4 = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    64, // vtxCount  8
    0, // vtxV0 9
    32, // triCount a
    GT_FLAG_NOMTX, // some_flag b
    NULL, // c
    gsDPNoOp(), // 10
};


gtStateL SignP2_2_StateL_5 = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    28, // vtxCount  8
    0, // vtxV0 9
    14, // triCount a
    GT_FLAG_NOMTX, // some_flag b
    NULL, // c
    gsDPNoOp(), // 10
};


gtGfx SignP2_2_GfxList[] = {
    {
        NULL,
        (gtState *)&SignP2_2_State,
        sign_Cube_mesh_vtx_0+0,
        SignP2_2_tris_0,
    },
    {
        NULL,
        (gtState *)&SignP2_2_StateL_0,
        sign_Cube_mesh_vtx_0+64,
        SignP2_2_tris_1,
    },
    {
        NULL,
        (gtState *)&SignP2_2_StateL_1,
        sign_Cube_mesh_vtx_0+128,
        SignP2_2_tris_2,
    },
    {
        NULL,
        (gtState *)&SignP2_2_StateL_2,
        sign_Cube_mesh_vtx_0+192,
        SignP2_2_tris_3,
    },
    {
        NULL,
        (gtState *)&SignP2_2_StateL_3,
        sign_Cube_mesh_vtx_0+256,
        SignP2_2_tris_4,
    },
    {
        NULL,
        (gtState *)&SignP2_2_StateL_4,
        sign_Cube_mesh_vtx_0+320,
        SignP2_2_tris_5,
    },
    {
        NULL,
        (gtState *)&SignP2_2_StateL_5,
        sign_Cube_mesh_vtx_0+384,
        SignP2_2_tris_6,
    },
};
OFUN(InGame_SignP2_2Loop);
Object2639 SignP2_2_Obj = {
    {200, 220, 1000},
    {0, 180, 0},
    {1.0, 1.0, 1.0},


    7, // gfxlist count
    &SignP2_2_GfxList, // gfxlist name

    MATERIAL_TEXTURE,
    PARAM_PACK(G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32),
    // canvas_P2Instructions2_rgba16,
    sign_P1Instructions_rgba16,

    NULL,
    InGame_SignP2_2Loop,
};

