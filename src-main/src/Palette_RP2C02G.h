/*	The PPU's video signal is prone to various subtle non-linearities that are best accounted for by using a measured but non-decoded signal.
*/
struct measuredValue RP2C02G[8][64] = {
{ // emph 0
	{ /* 00 */ 0.453845, 0.001895, 87.746887 },
	{ /* 01 */ 0.130823, 0.236163, 333.950537 },
	{ /* 02 */ 0.127188, 0.236030, 7.294646 },
	{ /* 03 */ 0.126619, 0.238060, 32.199612 },
	{ /* 04 */ 0.145683, 0.239526, 60.917175 },
	{ /* 05 */ 0.123431, 0.235874, 93.514137 },
	{ /* 06 */ 0.128676, 0.238346, 127.687729 },
	{ /* 07 */ 0.127366, 0.237970, 155.804230 },
	{ /* 08 */ 0.144844, 0.240267, 180.502991 },
	{ /* 09 */ 0.128629, 0.237767, 216.480545 },
	{ /* 0A */ 0.129508, 0.237791, 249.608025 },
	{ /* 0B */ 0.130217, 0.234553, 277.891289 },
	{ /* 0C */ 0.144699, 0.240685, 301.969704 },
	{ /* 0D */ -0.128030, 0.001015, 129.526199 },
	{ /* 0E */ 0.000000, 0.000000, 0.000000 },
	{ /* 0F */ 0.000000, 0.000000, 0.000000 },
	{ /* 10 */ 0.775026, 0.000932, 50.587509 },
	{ /* 11 */ 0.341781, 0.311315, 329.039463 },
	{ /* 12 */ 0.338039, 0.312992, 2.259023 },
	{ /* 13 */ 0.336407, 0.311723, 28.266245 },
	{ /* 14 */ 0.363051, 0.317798, 55.667923 },
	{ /* 15 */ 0.333917, 0.313511, 88.361923 },
	{ /* 16 */ 0.339273, 0.312909, 123.590294 },
	{ /* 17 */ 0.334754, 0.309986, 151.152084 },
	{ /* 18 */ 0.360678, 0.318914, 176.085739 },
	{ /* 19 */ 0.339247, 0.312816, 212.098221 },
	{ /* 1A */ 0.339238, 0.308918, 244.834908 },
	{ /* 1B */ 0.341433, 0.312832, 273.112350 },
	{ /* 1C */ 0.360186, 0.315016, 297.669048 },
	{ /* 1D */ 0.000626, 0.000733, 119.412605 },
	{ /* 1E */ 0.000000, 0.000000, 0.000000 },
	{ /* 1F */ 0.000000, 0.000000, 0.000000 },
	{ /* 20 */ 1.141785, 0.000513, 149.445313 },
	{ /* 21 */ 0.698706, 0.312909, 321.796398 },
	{ /* 22 */ 0.695260, 0.311823, 355.360687 },
	{ /* 23 */ 0.693131, 0.309362, 20.814838 },
	{ /* 24 */ 0.721552, 0.318721, 48.644527 },
	{ /* 25 */ 0.689517, 0.308533, 81.824181 },
	{ /* 26 */ 0.694130, 0.310515, 116.442192 },
	{ /* 27 */ 0.690040, 0.312567, 144.056793 },
	{ /* 28 */ 0.716490, 0.316252, 169.269928 },
	{ /* 29 */ 0.694745, 0.309488, 204.929291 },
	{ /* 2A */ 0.696223, 0.313996, 237.567711 },
	{ /* 2B */ 0.699466, 0.311227, 266.259628 },
	{ /* 2C */ 0.717323, 0.315912, 290.106705 },
	{ /* 2D */ 0.346946, 0.000664, 185.937744 },
	{ /* 2E */ 0.000000, 0.000000, 0.000000 },
	{ /* 2F */ 0.000000, 0.000000, 0.000000 },
	{ /* 30 */ 1.136349, 0.001130, 115.320679 },
	{ /* 31 */ 0.963197, 0.125947, 319.899391 },
	{ /* 32 */ 0.960300, 0.126513, 353.128162 },
	{ /* 33 */ 0.961030, 0.127336, 18.651388 },
	{ /* 34 */ 0.970677, 0.127684, 46.939732 },
	{ /* 35 */ 0.957911, 0.128592, 79.264557 },
	{ /* 36 */ 0.960561, 0.128702, 114.744522 },
	{ /* 37 */ 0.958946, 0.126047, 141.887878 },
	{ /* 38 */ 0.968485, 0.129257, 166.691208 },
	{ /* 39 */ 0.959624, 0.127152, 202.906036 },
	{ /* 3A */ 0.961622, 0.125860, 236.226723 },
	{ /* 3B */ 0.962065, 0.126337, 264.183960 },
	{ /* 3C */ 0.968670, 0.128543, 288.377220 },
	{ /* 3D */ 0.814154, 0.001275, 113.404190 },
	{ /* 3E */ 0.000000, 0.000000, 0.000000 },
	{ /* 3F */ 0.000000, 0.000000, 0.000000 }
},
{ // emph 1
	{ /* 00 */ 0.352128, 0.074959, 118.534073 },
	{ /* 01 */ 0.045290, 0.172985, 341.032190 },
	{ /* 02 */ 0.055259, 0.197663, 18.401636 },
	{ /* 03 */ 0.062428, 0.216844, 43.528755 },
	{ /* 04 */ 0.089964, 0.243883, 69.064545 },
	{ /* 05 */ 0.080967, 0.257227, 96.571091 },
	{ /* 06 */ 0.085577, 0.259783, 127.364250 },
	{ /* 07 */ 0.076876, 0.254413, 150.296967 },
	{ /* 08 */ 0.085907, 0.243681, 171.444672 },
	{ /* 09 */ 0.059505, 0.213549, 204.763458 },
	{ /* 0A */ 0.049820, 0.186052, 238.328056 },
	{ /* 0B */ 0.041558, 0.170040, 271.552864 },
	{ /* 0C */ 0.049916, 0.162833, 302.198719 },
	{ /* 0D */ -0.167221, 0.024090, 128.464508 },
	{ /* 0E */ 0.000000, 0.000000, 0.000000 },
	{ /* 0F */ 0.000000, 0.000000, 0.000000 },
	{ /* 10 */ 0.646968, 0.101950, 115.371819 },
	{ /* 11 */ 0.236444, 0.228234, 338.373663 },
	{ /* 12 */ 0.245090, 0.257567, 14.972709 },
	{ /* 13 */ 0.256781, 0.287233, 39.656872 },
	{ /* 14 */ 0.293435, 0.320884, 65.397987 },
	{ /* 15 */ 0.279616, 0.337234, 92.520020 },
	{ /* 16 */ 0.285481, 0.347101, 121.981972 },
	{ /* 17 */ 0.276782, 0.339375, 145.780212 },
	{ /* 18 */ 0.289363, 0.324418, 167.348251 },
	{ /* 19 */ 0.252861, 0.283598, 200.266144 },
	{ /* 1A */ 0.240175, 0.247847, 234.273994 },
	{ /* 1B */ 0.229913, 0.219330, 268.160477 },
	{ /* 1C */ 0.241954, 0.217109, 298.712883 },
	{ /* 1D */ -0.049142, 0.035585, 124.903915 },
	{ /* 1E */ 0.000000, 0.000000, 0.000000 },
	{ /* 1F */ 0.000000, 0.000000, 0.000000 },
	{ /* 20 */ 0.977738, 0.130789, 111.848404 },
	{ /* 21 */ 0.559128, 0.204397, 339.045174 },
	{ /* 22 */ 0.568390, 0.252612, 16.244423 },
	{ /* 23 */ 0.580548, 0.291351, 40.599537 },
	{ /* 24 */ 0.615567, 0.334833, 63.892269 },
	{ /* 25 */ 0.601045, 0.363752, 88.227898 },
	{ /* 26 */ 0.605142, 0.373649, 115.355194 },
	{ /* 27 */ 0.595741, 0.362706, 137.774506 },
	{ /* 28 */ 0.614583, 0.349780, 158.861938 },
	{ /* 29 */ 0.579574, 0.295702, 191.043594 },
	{ /* 2A */ 0.567615, 0.240039, 224.255814 },
	{ /* 2B */ 0.557251, 0.201384, 259.511284 },
	{ /* 2C */ 0.569010, 0.187422, 295.240891 },
	{ /* 2D */ 0.265136, 0.066798, 123.577461 },
	{ /* 2E */ 0.000000, 0.000000, 0.000000 },
	{ /* 2F */ 0.000000, 0.000000, 0.000000 },
	{ /* 30 */ 0.977272, 0.130219, 109.445961 },
	{ /* 31 */ 0.811761, 0.056605, 40.471436 },
	{ /* 32 */ 0.814641, 0.118761, 54.566219 },
	{ /* 33 */ 0.818977, 0.156858, 66.168457 },
	{ /* 34 */ 0.834499, 0.196325, 79.571053 },
	{ /* 35 */ 0.830165, 0.220124, 94.029488 },
	{ /* 36 */ 0.826109, 0.232693, 111.828522 },
	{ /* 37 */ 0.826312, 0.226294, 127.459480 },
	{ /* 38 */ 0.832287, 0.207357, 140.412476 },
	{ /* 39 */ 0.818466, 0.162401, 158.470352 },
	{ /* 3A */ 0.812424, 0.107941, 175.553391 },
	{ /* 3B */ 0.808483, 0.050985, 188.063507 },
	{ /* 3C */ 0.809757, 0.004569, 139.055313 },
	{ /* 3D */ 0.685405, 0.107213, 117.142418 },
	{ /* 3E */ 0.000000, 0.000000, 0.000000 },
	{ /* 3F */ 0.000000, 0.000000, 0.000000 }
},
{ // emph 2
	{ /* 00 */ 0.350122, 0.074497, 237.596573 },
	{ /* 01 */ 0.058576, 0.214838, 322.400879 },
	{ /* 02 */ 0.044772, 0.187272, 356.044821 },
	{ /* 03 */ 0.036783, 0.172489, 26.130716 },
	{ /* 04 */ 0.048216, 0.165618, 61.589218 },
	{ /* 05 */ 0.036626, 0.170293, 100.690155 },
	{ /* 06 */ 0.054246, 0.199452, 139.678101 },
	{ /* 07 */ 0.060318, 0.219233, 167.281113 },
	{ /* 08 */ 0.087280, 0.242127, 189.458084 },
	{ /* 09 */ 0.083033, 0.257400, 220.171005 },
	{ /* 0A */ 0.086743, 0.260697, 248.888504 },
	{ /* 0B */ 0.079252, 0.253336, 272.571983 },
	{ /* 0C */ 0.084958, 0.245298, 293.590569 },
	{ /* 0D */ -0.170738, 0.022336, 247.010750 },
	{ /* 0E */ 0.000000, 0.000000, 0.000000 },
	{ /* 0F */ 0.000000, 0.000000, 0.000000 },
	{ /* 10 */ 0.645427, 0.101922, 235.407051 },
	{ /* 11 */ 0.255682, 0.286088, 317.438965 },
	{ /* 12 */ 0.236936, 0.249041, 352.041481 },
	{ /* 13 */ 0.226500, 0.222926, 22.363562 },
	{ /* 14 */ 0.243516, 0.217734, 57.420761 },
	{ /* 15 */ 0.226992, 0.226007, 97.434113 },
	{ /* 16 */ 0.246955, 0.258790, 136.391418 },
	{ /* 17 */ 0.255103, 0.288415, 162.976364 },
	{ /* 18 */ 0.289516, 0.322669, 185.891617 },
	{ /* 19 */ 0.285442, 0.340423, 215.976791 },
	{ /* 1A */ 0.285613, 0.346393, 243.764641 },
	{ /* 1B */ 0.279531, 0.340597, 267.859619 },
	{ /* 1C */ 0.288525, 0.323172, 288.815071 },
	{ /* 1D */ -0.050085, 0.035549, 245.733849 },
	{ /* 1E */ 0.000000, 0.000000, 0.000000 },
	{ /* 1F */ 0.000000, 0.000000, 0.000000 },
	{ /* 20 */ 0.979643, 0.131435, 230.561874 },
	{ /* 21 */ 0.584016, 0.299034, 307.742966 },
	{ /* 22 */ 0.565391, 0.240997, 341.326216 },
	{ /* 23 */ 0.554326, 0.205950, 12.867361 },
	{ /* 24 */ 0.570122, 0.189634, 53.480515 },
	{ /* 25 */ 0.553018, 0.202112, 97.937233 },
	{ /* 26 */ 0.569937, 0.253103, 137.119186 },
	{ /* 27 */ 0.577705, 0.295348, 163.003143 },
	{ /* 28 */ 0.613596, 0.335157, 184.036163 },
	{ /* 29 */ 0.607482, 0.365449, 210.679367 },
	{ /* 2A */ 0.606172, 0.375842, 236.118523 },
	{ /* 2B */ 0.603780, 0.363274, 259.263199 },
	{ /* 2C */ 0.615537, 0.348474, 279.531769 },
	{ /* 2D */ 0.264676, 0.066886, 242.085426 },
	{ /* 2E */ 0.000000, 0.000000, 0.000000 },
	{ /* 2F */ 0.000000, 0.000000, 0.000000 },
	{ /* 30 */ 0.978814, 0.131071, 229.976761 },
	{ /* 31 */ 0.821455, 0.163892, 276.358330 },
	{ /* 32 */ 0.812221, 0.107556, 293.918907 },
	{ /* 33 */ 0.808456, 0.057679, 306.204021 },
	{ /* 34 */ 0.812070, 0.001909, 225.861328 },
	{ /* 35 */ 0.809939, 0.054935, 159.378815 },
	{ /* 36 */ 0.816759, 0.118285, 175.492203 },
	{ /* 37 */ 0.819689, 0.161016, 188.515991 },
	{ /* 38 */ 0.833564, 0.193708, 200.154160 },
	{ /* 39 */ 0.834828, 0.222574, 216.537628 },
	{ /* 3A */ 0.828316, 0.231173, 234.034706 },
	{ /* 3B */ 0.829806, 0.224794, 249.645287 },
	{ /* 3C */ 0.833299, 0.206581, 262.021019 },
	{ /* 3D */ 0.686401, 0.105325, 237.704636 },
	{ /* 3E */ 0.000000, 0.000000, 0.000000 },
	{ /* 3F */ 0.000000, 0.000000, 0.000000 }
},
{ // emph 3
	{ /* 00 */ 0.290807, 0.043522, 177.240097 },
	{ /* 01 */ 0.014730, 0.175843, 331.078768 },
	{ /* 02 */ 0.012795, 0.171013, 7.201829 },
	{ /* 03 */ 0.009649, 0.172659, 34.750759 },
	{ /* 04 */ 0.030257, 0.185095, 64.989464 },
	{ /* 05 */ 0.019306, 0.193461, 100.655128 },
	{ /* 06 */ 0.032287, 0.214305, 135.701874 },
	{ /* 07 */ 0.033474, 0.226081, 159.278152 },
	{ /* 08 */ 0.048643, 0.230219, 180.613174 },
	{ /* 09 */ 0.035576, 0.220249, 210.574539 },
	{ /* 0A */ 0.028080, 0.205902, 241.542946 },
	{ /* 0B */ 0.019685, 0.191363, 271.487556 },
	{ /* 0C */ 0.025672, 0.182838, 297.741093 },
	{ /* 0D */ -0.189400, 0.012955, 190.360458 },
	{ /* 0E */ 0.000000, 0.000000, 0.000000 },
	{ /* 0F */ 0.000000, 0.000000, 0.000000 },
	{ /* 10 */ 0.564294, 0.058927, 174.688843 },
	{ /* 11 */ 0.193731, 0.229574, 328.761650 },
	{ /* 12 */ 0.189972, 0.224187, 5.170427 },
	{ /* 13 */ 0.192206, 0.230615, 32.512726 },
	{ /* 14 */ 0.214268, 0.238905, 63.706104 },
	{ /* 15 */ 0.198151, 0.255269, 98.205551 },
	{ /* 16 */ 0.214852, 0.285087, 131.751434 },
	{ /* 17 */ 0.218450, 0.299038, 156.239944 },
	{ /* 18 */ 0.239739, 0.305907, 177.458588 },
	{ /* 19 */ 0.222151, 0.296990, 207.438889 },
	{ /* 1A */ 0.213048, 0.275310, 239.028511 },
	{ /* 1B */ 0.202131, 0.251270, 268.611015 },
	{ /* 1C */ 0.209633, 0.244421, 294.785019 },
	{ /* 1D */ -0.077228, 0.020906, 182.335205 },
	{ /* 1E */ 0.000000, 0.000000, 0.000000 },
	{ /* 1F */ 0.000000, 0.000000, 0.000000 },
	{ /* 20 */ 0.871943, 0.074550, 171.250626 },
	{ /* 21 */ 0.496515, 0.219543, 320.670227 },
	{ /* 22 */ 0.492808, 0.213762, 0.256635 },
	{ /* 23 */ 0.494903, 0.215326, 30.973372 },
	{ /* 24 */ 0.518875, 0.236569, 62.623215 },
	{ /* 25 */ 0.499472, 0.263438, 96.668839 },
	{ /* 26 */ 0.513138, 0.295470, 127.432449 },
	{ /* 27 */ 0.514181, 0.310531, 150.499786 },
	{ /* 28 */ 0.540010, 0.324040, 171.972061 },
	{ /* 29 */ 0.524691, 0.314011, 201.610550 },
	{ /* 2A */ 0.514533, 0.285309, 231.634033 },
	{ /* 2B */ 0.504256, 0.261791, 260.375717 },
	{ /* 2C */ 0.511726, 0.240125, 286.545067 },
	{ /* 2D */ 0.211793, 0.039249, 181.221191 },
	{ /* 2E */ 0.000000, 0.000000, 0.000000 },
	{ /* 2F */ 0.000000, 0.000000, 0.000000 },
	{ /* 30 */ 0.869944, 0.075329, 170.325989 },
	{ /* 31 */ 0.723642, 0.058243, 291.508118 },
	{ /* 32 */ 0.720208, 0.040745, 1.861921 },
	{ /* 33 */ 0.721601, 0.057268, 53.695461 },
	{ /* 34 */ 0.731524, 0.088999, 88.965393 },
	{ /* 35 */ 0.720505, 0.120875, 114.718941 },
	{ /* 36 */ 0.725196, 0.153869, 136.588898 },
	{ /* 37 */ 0.730183, 0.170209, 155.119781 },
	{ /* 38 */ 0.739874, 0.175654, 170.356674 },
	{ /* 39 */ 0.734963, 0.170128, 190.977386 },
	{ /* 3A */ 0.725467, 0.145761, 215.260498 },
	{ /* 3B */ 0.721857, 0.117865, 236.467979 },
	{ /* 3C */ 0.722999, 0.091803, 258.504051 },
	{ /* 3D */ 0.602280, 0.060366, 178.582581 },
	{ /* 3E */ 0.000000, 0.000000, 0.000000 },
	{ /* 3F */ 0.000000, 0.000000, 0.000000 }
},
{ // emph 4
	{ /* 00 */ 0.353374, 0.075082, 0.702944 },
	{ /* 01 */ 0.085652, 0.255240, 337.858824 },
	{ /* 02 */ 0.085814, 0.261934, 6.737377 },
	{ /* 03 */ 0.079875, 0.258344, 28.570408 },
	{ /* 04 */ 0.088079, 0.246014, 51.850643 },
	{ /* 05 */ 0.056256, 0.219411, 82.086853 },
	{ /* 06 */ 0.048467, 0.192881, 117.494354 },
	{ /* 07 */ 0.037058, 0.169876, 149.814041 },
	{ /* 08 */ 0.050482, 0.166576, 180.523483 },
	{ /* 09 */ 0.043898, 0.174193, 224.628204 },
	{ /* 0A */ 0.056420, 0.195258, 261.843468 },
	{ /* 0B */ 0.066206, 0.221606, 289.113899 },
	{ /* 0C */ 0.088614, 0.241981, 312.001335 },
	{ /* 0D */ -0.170042, 0.023481, 12.039941 },
	{ /* 0E */ 0.000000, 0.000000, 0.000000 },
	{ /* 0F */ 0.000000, 0.000000, 0.000000 },
	{ /* 10 */ 0.648507, 0.101826, 357.544334 },
	{ /* 11 */ 0.288867, 0.342236, 333.070782 },
	{ /* 12 */ 0.287294, 0.351002, 1.616563 },
	{ /* 13 */ 0.279945, 0.341225, 23.387627 },
	{ /* 14 */ 0.295610, 0.330676, 47.218025 },
	{ /* 15 */ 0.252503, 0.290208, 78.158768 },
	{ /* 16 */ 0.242003, 0.249891, 113.551842 },
	{ /* 17 */ 0.227832, 0.223394, 145.333939 },
	{ /* 18 */ 0.241746, 0.216535, 177.624619 },
	{ /* 19 */ 0.233928, 0.224405, 221.628357 },
	{ /* 1A */ 0.249333, 0.258063, 257.603577 },
	{ /* 1B */ 0.264352, 0.292085, 285.356636 },
	{ /* 1C */ 0.292755, 0.318124, 307.925449 },
	{ /* 1D */ -0.049892, 0.035328, 8.493227 },
	{ /* 1E */ 0.000000, 0.000000, 0.000000 },
	{ /* 1F */ 0.000000, 0.000000, 0.000000 },
	{ /* 20 */ 0.984498, 0.131723, 353.468222 },
	{ /* 21 */ 0.612710, 0.364970, 329.142122 },
	{ /* 22 */ 0.606017, 0.371810, 354.319502 },
	{ /* 23 */ 0.603353, 0.369569, 14.817264 },
	{ /* 24 */ 0.620737, 0.350459, 38.758461 },
	{ /* 25 */ 0.580046, 0.301236, 67.703148 },
	{ /* 26 */ 0.571763, 0.246957, 102.151505 },
	{ /* 27 */ 0.554368, 0.206139, 137.324539 },
	{ /* 28 */ 0.570538, 0.190197, 172.782791 },
	{ /* 29 */ 0.559674, 0.205424, 221.283875 },
	{ /* 2A */ 0.575108, 0.251338, 258.619652 },
	{ /* 2B */ 0.586510, 0.293144, 285.684181 },
	{ /* 2C */ 0.614463, 0.335028, 305.456978 },
	{ /* 2D */ 0.266805, 0.067033, 6.009111 },
	{ /* 2E */ 0.000000, 0.000000, 0.000000 },
	{ /* 2F */ 0.000000, 0.000000, 0.000000 },
	{ /* 30 */ 0.981966, 0.131651, 351.714167 },
	{ /* 31 */ 0.839190, 0.221188, 334.971992 },
	{ /* 32 */ 0.832916, 0.232574, 352.438247 },
	{ /* 33 */ 0.832333, 0.227610, 6.705750 },
	{ /* 34 */ 0.838889, 0.210365, 21.218775 },
	{ /* 35 */ 0.821595, 0.168054, 37.936165 },
	{ /* 36 */ 0.816981, 0.114024, 56.207520 },
	{ /* 37 */ 0.810718, 0.057320, 68.744980 },
	{ /* 38 */ 0.815418, 0.005562, 66.997948 },
	{ /* 39 */ 0.815099, 0.054724, 283.934464 },
	{ /* 3A */ 0.819220, 0.116074, 298.588615 },
	{ /* 3B */ 0.825040, 0.160470, 311.367863 },
	{ /* 3C */ 0.837794, 0.192563, 323.126923 },
	{ /* 3D */ 0.688642, 0.105995, 0.114273 },
	{ /* 3E */ 0.000000, 0.000000, 0.000000 },
	{ /* 3F */ 0.000000, 0.000000, 0.000000 }
},
{ // emph 5
	{ /* 00 */ 0.294170, 0.045528, 59.474621 },
	{ /* 01 */ 0.028835, 0.195850, 341.341404 },
	{ /* 02 */ 0.034069, 0.214981, 14.798910 },
	{ /* 03 */ 0.037291, 0.225664, 36.504757 },
	{ /* 04 */ 0.054889, 0.233706, 59.887821 },
	{ /* 05 */ 0.034702, 0.223410, 87.318687 },
	{ /* 06 */ 0.028526, 0.206675, 120.012871 },
	{ /* 07 */ 0.018801, 0.192772, 148.983978 },
	{ /* 08 */ 0.027949, 0.182438, 176.266159 },
	{ /* 09 */ 0.012336, 0.173365, 213.441162 },
	{ /* 0A */ 0.015167, 0.173000, 249.382462 },
	{ /* 0B */ 0.017132, 0.174219, 280.663292 },
	{ /* 0C */ 0.031001, 0.181541, 306.681362 },
	{ /* 0D */ -0.189616, 0.015846, 68.764259 },
	{ /* 0E */ 0.000000, 0.000000, 0.000000 },
	{ /* 0F */ 0.000000, 0.000000, 0.000000 },
	{ /* 10 */ 0.567416, 0.060164, 55.373440 },
	{ /* 11 */ 0.209438, 0.257752, 338.963465 },
	{ /* 12 */ 0.216914, 0.283071, 10.730173 },
	{ /* 13 */ 0.222670, 0.299829, 33.133984 },
	{ /* 14 */ 0.245329, 0.307646, 57.115677 },
	{ /* 15 */ 0.220572, 0.298170, 84.247047 },
	{ /* 16 */ 0.213745, 0.277957, 117.442703 },
	{ /* 17 */ 0.198831, 0.254756, 146.394012 },
	{ /* 18 */ 0.211398, 0.243882, 172.921799 },
	{ /* 19 */ 0.193816, 0.230183, 211.131668 },
	{ /* 1A */ 0.196385, 0.224643, 247.094154 },
	{ /* 1B */ 0.196457, 0.226575, 278.209618 },
	{ /* 1C */ 0.214274, 0.240304, 304.887421 },
	{ /* 1D */ -0.076388, 0.021607, 69.256058 },
	{ /* 1E */ 0.000000, 0.000000, 0.000000 },
	{ /* 1F */ 0.000000, 0.000000, 0.000000 },
	{ /* 20 */ 0.876285, 0.076579, 50.691456 },
	{ /* 21 */ 0.511533, 0.265054, 336.895369 },
	{ /* 22 */ 0.514458, 0.297374, 6.431756 },
	{ /* 23 */ 0.520162, 0.311145, 27.931568 },
	{ /* 24 */ 0.546423, 0.327651, 51.200893 },
	{ /* 25 */ 0.525003, 0.315945, 78.009315 },
	{ /* 26 */ 0.516973, 0.287867, 110.084747 },
	{ /* 27 */ 0.501192, 0.261911, 137.661285 },
	{ /* 28 */ 0.514121, 0.243519, 165.126816 },
	{ /* 29 */ 0.496497, 0.217667, 204.277847 },
	{ /* 2A */ 0.496837, 0.210505, 242.988152 },
	{ /* 2B */ 0.502212, 0.219778, 276.887817 },
	{ /* 2C */ 0.520263, 0.233144, 304.387375 },
	{ /* 2D */ 0.214439, 0.039712, 63.242001 },
	{ /* 2E */ 0.000000, 0.000000, 0.000000 },
	{ /* 2F */ 0.000000, 0.000000, 0.000000 },
	{ /* 30 */ 0.875162, 0.077023, 51.570217 },
	{ /* 31 */ 0.729942, 0.122844, 355.968449 },
	{ /* 32 */ 0.730254, 0.153676, 16.863560 },
	{ /* 33 */ 0.734407, 0.170712, 33.332737 },
	{ /* 34 */ 0.745368, 0.177382, 50.289833 },
	{ /* 35 */ 0.736318, 0.172911, 68.797401 },
	{ /* 36 */ 0.729329, 0.148964, 93.554733 },
	{ /* 37 */ 0.721813, 0.121655, 114.482178 },
	{ /* 38 */ 0.726551, 0.094876, 136.594299 },
	{ /* 39 */ 0.724894, 0.058963, 172.847229 },
	{ /* 3A */ 0.724017, 0.039657, 243.306580 },
	{ /* 3B */ 0.726010, 0.057639, 304.302296 },
	{ /* 3C */ 0.733538, 0.087443, 331.497705 },
	{ /* 3D */ 0.603351, 0.062669, 58.614750 },
	{ /* 3E */ 0.000000, 0.000000, 0.000000 },
	{ /* 3F */ 0.000000, 0.000000, 0.000000 }
},
{ // emph 6
	{ /* 00 */ 0.292968, 0.041397, 299.834873 },
	{ /* 01 */ 0.038361, 0.222019, 328.220770 },
	{ /* 02 */ 0.029025, 0.207228, 359.600748 },
	{ /* 03 */ 0.020403, 0.192358, 26.794697 },
	{ /* 04 */ 0.030511, 0.185007, 57.030689 },
	{ /* 05 */ 0.011485, 0.176597, 90.755447 },
	{ /* 06 */ 0.014824, 0.174465, 128.642792 },
	{ /* 07 */ 0.012620, 0.174169, 158.690659 },
	{ /* 08 */ 0.029736, 0.182743, 185.397720 },
	{ /* 09 */ 0.026881, 0.194763, 224.680054 },
	{ /* 0A */ 0.034774, 0.212028, 257.228050 },
	{ /* 0B */ 0.039679, 0.225199, 281.807259 },
	{ /* 0C */ 0.051511, 0.228982, 302.553951 },
	{ /* 0D */ -0.187363, 0.012154, 314.597237 },
	{ /* 0E */ 0.000000, 0.000000, 0.000000 },
	{ /* 0F */ 0.000000, 0.000000, 0.000000 },
	{ /* 10 */ 0.565564, 0.055845, 295.848572 },
	{ /* 11 */ 0.227555, 0.297888, 324.000961 },
	{ /* 12 */ 0.213285, 0.274905, 356.018618 },
	{ /* 13 */ 0.201265, 0.253926, 22.330297 },
	{ /* 14 */ 0.213793, 0.246142, 52.483898 },
	{ /* 15 */ 0.188872, 0.231017, 87.338890 },
	{ /* 16 */ 0.194483, 0.228117, 124.625023 },
	{ /* 17 */ 0.190906, 0.229687, 155.018951 },
	{ /* 18 */ 0.214164, 0.239245, 182.733093 },
	{ /* 19 */ 0.205261, 0.256855, 220.638779 },
	{ /* 1A */ 0.217216, 0.282452, 252.181206 },
	{ /* 1B */ 0.224524, 0.296726, 277.562172 },
	{ /* 1C */ 0.241337, 0.303874, 298.116283 },
	{ /* 1D */ -0.077754, 0.019234, 305.284653 },
	{ /* 1E */ 0.000000, 0.000000, 0.000000 },
	{ /* 1F */ 0.000000, 0.000000, 0.000000 },
	{ /* 20 */ 0.874987, 0.071900, 292.381500 },
	{ /* 21 */ 0.528803, 0.312405, 319.623154 },
	{ /* 22 */ 0.515440, 0.286947, 349.874773 },
	{ /* 23 */ 0.503432, 0.264709, 15.662116 },
	{ /* 24 */ 0.516151, 0.242561, 46.051155 },
	{ /* 25 */ 0.491464, 0.221559, 81.038429 },
	{ /* 26 */ 0.496185, 0.215978, 121.829956 },
	{ /* 27 */ 0.495476, 0.218232, 154.848999 },
	{ /* 28 */ 0.519069, 0.235115, 182.862488 },
	{ /* 29 */ 0.506408, 0.264871, 220.034134 },
	{ /* 2A */ 0.516212, 0.294071, 249.179245 },
	{ /* 2B */ 0.520767, 0.309931, 273.561691 },
	{ /* 2C */ 0.543339, 0.321407, 294.071236 },
	{ /* 2D */ 0.213145, 0.037328, 304.058819 },
	{ /* 2E */ 0.000000, 0.000000, 0.000000 },
	{ /* 2F */ 0.000000, 0.000000, 0.000000 },
	{ /* 30 */ 0.873158, 0.072064, 291.467606 },
	{ /* 31 */ 0.739584, 0.167526, 308.391483 },
	{ /* 32 */ 0.730175, 0.145655, 333.045237 },
	{ /* 33 */ 0.723099, 0.122462, 352.697998 },
	{ /* 34 */ 0.725947, 0.094042, 18.177101 },
	{ /* 35 */ 0.722641, 0.061650, 51.039089 },
	{ /* 36 */ 0.722526, 0.043726, 120.781120 },
	{ /* 37 */ 0.723327, 0.059332, 175.971451 },
	{ /* 38 */ 0.732298, 0.085705, 207.785431 },
	{ /* 39 */ 0.726556, 0.121600, 236.205399 },
	{ /* 3A */ 0.728894, 0.151197, 257.511795 },
	{ /* 3B */ 0.734003, 0.166380, 276.104172 },
	{ /* 3C */ 0.742453, 0.171793, 291.387878 },
	{ /* 3D */ 0.603215, 0.059012, 298.539452 },
	{ /* 3E */ 0.000000, 0.000000, 0.000000 },
	{ /* 3F */ 0.000000, 0.000000, 0.000000 }
},
{ // emph 7
	{ /* 00 */ 0.258763, 0.000298, 104.522171 },
	{ /* 01 */ 0.006081, 0.187426, 334.152685 },
	{ /* 02 */ 0.003537, 0.185251, 8.011382 },
	{ /* 03 */ 0.003692, 0.187892, 32.630760 },
	{ /* 04 */ 0.018386, 0.189137, 61.042625 },
	{ /* 05 */ -0.000180, 0.185183, 93.578331 },
	{ /* 06 */ 0.004123, 0.187066, 128.195389 },
	{ /* 07 */ 0.001957, 0.187043, 156.534409 },
	{ /* 08 */ 0.017887, 0.188132, 180.932770 },
	{ /* 09 */ 0.004121, 0.185566, 216.450165 },
	{ /* 0A */ 0.004473, 0.186686, 249.730110 },
	{ /* 0B */ 0.005263, 0.183811, 278.329132 },
	{ /* 0C */ 0.017626, 0.189135, 302.190186 },
	{ /* 0D */ -0.197195, 0.000708, 184.666016 },
	{ /* 0E */ 0.000000, 0.000000, 0.000000 },
	{ /* 0F */ 0.000000, 0.000000, 0.000000 },
	{ /* 10 */ 0.519506, 0.001402, 345.989453 },
	{ /* 11 */ 0.180826, 0.245387, 331.025213 },
	{ /* 12 */ 0.177017, 0.246680, 4.372335 },
	{ /* 13 */ 0.177819, 0.247810, 30.067219 },
	{ /* 14 */ 0.199508, 0.249467, 58.483711 },
	{ /* 15 */ 0.173344, 0.248038, 90.546768 },
	{ /* 16 */ 0.177904, 0.249221, 125.458656 },
	{ /* 17 */ 0.174909, 0.246395, 153.521347 },
	{ /* 18 */ 0.195552, 0.251930, 178.123962 },
	{ /* 19 */ 0.178656, 0.247712, 214.037979 },
	{ /* 1A */ 0.179713, 0.246016, 246.975250 },
	{ /* 1B */ 0.179479, 0.247033, 275.058952 },
	{ /* 1C */ 0.195030, 0.250144, 299.641869 },
	{ /* 1D */ -0.092459, 0.000514, 15.389801 },
	{ /* 1E */ 0.000000, 0.000000, 0.000000 },
	{ /* 1F */ 0.000000, 0.000000, 0.000000 },
	{ /* 20 */ 0.813679, 0.000447, 251.711166 },
	{ /* 21 */ 0.468742, 0.252911, 326.117455 },
	{ /* 22 */ 0.465202, 0.252552, 359.717998 },
	{ /* 23 */ 0.464342, 0.250324, 24.869032 },
	{ /* 24 */ 0.485470, 0.257954, 53.024635 },
	{ /* 25 */ 0.462754, 0.251429, 86.284088 },
	{ /* 26 */ 0.466659, 0.251596, 120.879967 },
	{ /* 27 */ 0.462415, 0.252844, 148.049194 },
	{ /* 28 */ 0.484134, 0.253949, 173.498871 },
	{ /* 29 */ 0.465588, 0.250568, 209.321686 },
	{ /* 2A */ 0.466260, 0.251379, 241.942154 },
	{ /* 2B */ 0.468756, 0.251960, 270.510651 },
	{ /* 2C */ 0.484967, 0.253970, 294.383942 },
	{ /* 2D */ 0.183283, 0.001453, 167.712158 },
	{ /* 2E */ 0.000000, 0.000000, 0.000000 },
	{ /* 2F */ 0.000000, 0.000000, 0.000000 },
	{ /* 30 */ 0.811456, 0.001157, 102.513603 },
	{ /* 31 */ 0.673860, 0.100731, 323.878174 },
	{ /* 32 */ 0.672626, 0.101768, 357.425817 },
	{ /* 33 */ 0.672057, 0.101875, 23.131130 },
	{ /* 34 */ 0.680359, 0.102691, 50.864731 },
	{ /* 35 */ 0.670860, 0.101757, 83.207710 },
	{ /* 36 */ 0.672560, 0.102791, 116.784698 },
	{ /* 37 */ 0.670265, 0.103271, 145.109543 },
	{ /* 38 */ 0.680399, 0.103445, 169.896912 },
	{ /* 39 */ 0.672779, 0.101846, 206.836166 },
	{ /* 3A */ 0.672332, 0.100194, 239.178528 },
	{ /* 3B */ 0.672950, 0.100619, 267.849220 },
	{ /* 3C */ 0.679132, 0.101904, 291.795830 },
	{ /* 3D */ 0.552438, 0.000975, 104.825691 },
	{ /* 3E */ 0.000000, 0.000000, 0.000000 },
	{ /* 3F */ 0.000000, 0.000000, 0.000000 }
}
};