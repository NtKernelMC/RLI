#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
#include "xorstr.h"

static std::string code = xorstr_(R"STUB(-- by rdror && NtKernelMC
-- Settings
local mr, mg, mb, ma = 0, 155, 0, 170 
local SIZE_SEND = 5
local SIZE_TAKE = 1.5
local JOB_INT = 5 
local TP_SPEED = 100
local TIME_TO_NEXT_MARKER = 2000
-- For stable work
local active = false
local markers = {}
local helperMarker
local route = 0
local index = 0
local tempMarker
local tempMarkerIndex = 0
local tempMarkers = {}
local nextMarker
local oldIndex = 0
local tempIndex = 0
local typeMarker
setDebugViewActive(true)

)STUB");

static std::string code2 = xorstr_(R"STUB(

-- Table with original markers
local COriginalPoints = { -- originl markers
	-- Take markers
	[1] = {33.760, -243.963, 390.200},
	[2] = {14.374, -227.315, 390.20},
	[3] = {14.186, -286.529, 390.200},
	[4] = {28.300, -308.945, 390.200},
	[5] = {28.300, -332.000, 390.200},
	[6] = {27.795, -277.042, 390.200},
	-- Send markers
	[7] = {50.362, -242.500, 390.200},
	[8] = {50.362, -232.000, 390.200},
	[9] = {50.362, -223.500, 390.200},

}
-- Table with helper markers
local CHelpersPoints = { -- [route] = {[index] = {x, y, z}}
	[1] = {
		[1] = {
			{43.231922149658, -240.54507446289, 390},
			{41.179622650146, -240.87274169922, 390},
			{39.115249633789, -241.65289306641, 390},
		},
		[2] = {
			{43.238021850586, -240.48854064941, 390},
			{41.970184326172, -240.30575561523, 390},
			{39.768932342529, -238.79501342773, 390},
			{36.610702514648, -236.06340026855, 390},
			{32.336643218994, -231.82144165039, 390},
			{29.947128295898, -229.62617492676, 390},
			{27.724315643311, -227.4714050293, 390},
			{25.596134185791, -226.45431518555, 390},
			{23.113134384155, -226.19667053223, 390},
			{20.839906692505, -226.3518371582, 390},
		},
		[3] = {
			{41.784328460693, -240.55085754395, 390},
			{36.739162445068, -243.1827545166, 390},
			{34.038867950439, -245.9109954834, 390},
			{26.755882263184, -256.58474731445, 390},
			{21.346004486084, -266.7060546875, 390},
			{17.189472198486, -275.86972045898, 390},
			{16.199819564819, -279.03994750977, 390},
		},
		[4] = {
			{42.899719238281, -240.56228637695, 390},
			{41.547176361084, -241.76515197754, 390},
			{40.722011566162, -243.45942687988, 390},
			{39.916175842285, -246.49461364746, 390},
			{37.488800048828, -258.39428710938, 390},
			{33.821468353271, -279.86505126953, 390},
			{32.809257507324, -282.32934570313, 390},
			{30.720735549927, -285.67266845703, 390},
			{29.540260314941, -289.96221923828, 390},
			{28.737987518311, -295.66137695313, 390},
		},

)STUB");

static std::string code3 = xorstr_(R"STUB(

		[5] = {
			{42.899719238281, -240.56228637695, 390},
			{41.547176361084, -241.76515197754, 390},
			{40.722011566162, -243.45942687988, 390},
			{39.916175842285, -246.49461364746, 390},
			{37.488800048828, -258.39428710938, 390},
			{33.821468353271, -279.86505126953, 390},
			{32.809257507324, -282.32934570313, 390},
			{30.720735549927, -285.67266845703, 390},
			{29.540260314941, -289.96221923828, 390},
			{28.737987518311, -295.66137695313, 390},
		},
		[6] = {
			{43.025054931641, -240.6374206543, 390},
			{39.764499664307, -241.38450622559, 390},
			{38.193313598633, -243.70159912109, 390},
			{36.332778930664, -247.75218200684, 390},
			{33.134422302246, -257.91271972656, 390},
		}
	},
	[2] = {
		[1] = {
			{43.119789123535, -231.66828918457, 390},
			{41.821617126465, -232.75024414063, 390},
			{40.517520904541, -234.43817138672, 390},
		},
		[2] = {
			{42.97435760498, -231.60186767578, 390},
			{41.044933319092, -230.83708190918, 390},
			{37.445442199707, -229.6227722168, 390},
			{33.810443878174, -228.63803100586, 390},
			{28.967792510986, -227.90211486816, 390},
			{23.649257659912, -227.64924621582, 390},
		},
		[3] = {
			{42.959651947021, -232.06939697266, 390},
			{41.782772064209, -232.89874267578, 390},
			{40.147666931152, -235.24186706543, 390},
			{28.281337738037, -256.34051513672, 390},
			{22.885074615479, -266.21856689453, 390},
			{18.53391456604, -275.26538085938, 390},
			{15.735283851624, -282.08932495117, 390},

		},
		[4] = {
			{43.136775970459, -232.39086914063, 390},
			{42.043006896973, -233.01579284668, 390},
			{40.869110107422, -234.74792480469, 390},
			{39.832336425781, -237.16513061523, 390},
			{38.539813995361, -244.91995239258, 390},
			{33.592479705811, -281.48547363281, 390},
			{32.790634155273, -283.70739746094, 390},
			{30.77748298645, -287.08782958984, 390},
			{29.185464859009, -292.68502807617, 390},
			{28.652914047241, -296.58392333984, 390},
		},
		[5] = {
			{43.136775970459, -232.39086914063, 390},
			{42.043006896973, -233.01579284668, 390},
			{40.869110107422, -234.74792480469, 390},
			{39.832336425781, -237.16513061523, 390},
			{38.539813995361, -244.91995239258, 390},
			{33.592479705811, -281.48547363281, 390},
			{32.790634155273, -283.70739746094, 390},
			{30.77748298645, -287.08782958984, 390},
			{29.185464859009, -292.68502807617, 390},
			{28.652914047241, -296.58392333984, 390},
		},
		[6] = {
			{42.443420410156, -232.15982055664, 390},
			{41.431713104248, -233.25576782227, 390},
			{39.945400238037, -236.22593688965, 390},
			{34.835803985596, -252.12225341797, 390},
		}
	},

)STUB");

static std::string code4 = xorstr_(R"STUB(

	[3] = {
		[1] = {
			{43.249164581299, -223.96922302246, 390},
			{41.751220703125, -224.31970214844, 390},
			{39.957962036133, -225.80947875977, 390},
			{38.577732086182, -228.38354492188, 390},
			{37.506290435791, -231.13182067871, 390},
			{35.888977050781, -236.1830291748, 390},
		},
		[2] = {
			{44.250961303711, -223.69624328613, 390},
		},
		[3] = {
			{42.417072296143, -223.98686218262, 390},
			{40.837535858154, -225.28871154785, 390},
			{38.747005462646, -228.26214599609, 390},
			{36.874225616455, -232.94024658203, 390},
			{33.868556976318, -247.18824768066, 390},
			{32.938381195068, -249.02520751953, 390},
			{28.351383209229, -256.98760986328, 390},
			{22.543586730957, -266.21151733398, 390},
			{21.871156692505, -267.5661315918, 390},
			{17.269186019897, -279.11599731445, 390},
		},
		[4] = {
			{43.068992614746, -223.9186706543, 390},
			{41.548633575439, -224.81518554688, 390},
			{40.219650268555, -226.39448547363, 390},
			{38.915500640869, -228.71778869629, 390},
			{37.548942565918, -232.34719848633, 390},
			{36.369205474854, -237.53080749512, 390},
			{35.572761535645, -244.85466003418, 390},
			{33.774337768555, -280.31427001953, 390},
			{32.982139587402, -282.73901367188, 390},
			{31.066837310791, -285.4270324707, 390},
			{30.181873321533, -288.25094604492, 390},
			{28.976623535156, -293.33578491211, 390},
		},
		[5] = {
			{43.068992614746, -223.9186706543, 390},
			{41.548633575439, -224.81518554688, 390},
			{40.219650268555, -226.39448547363, 390},
			{38.915500640869, -228.71778869629, 390},
			{37.548942565918, -232.34719848633, 390},
			{36.369205474854, -237.53080749512, 390},
			{35.572761535645, -244.85466003418, 390},
			{33.774337768555, -280.31427001953, 390},
			{32.982139587402, -282.73901367188, 390},
			{31.066837310791, -285.4270324707, 390},
			{30.181873321533, -288.25094604492, 390},
			{28.976623535156, -293.33578491211, 390},
		},
		[6] = {
			{42.752281188965, -223.8356628418, 390},
			{41.676261901855, -224.66743469238, 390},
			{40.652603149414, -226.07737731934, 390},
			{38.778797149658, -229.43455505371, 390},
			{37.966426849365, -232.66096496582, 390},
			{33.664207458496, -253.17517089844, 390},
		}
	}
}
)STUB");

static std::string code5 = xorstr_(R"STUB(
local MIN_TIME_TO_STOP = 15000 -- â ìñ
local MAX_TIME_TO_STOP = 35000 -- â ì

local MIN_STOP_TIME = 1000
local MAX_STOP_TIME = 5000

local PARSE_INTERVAL = 7000
local ALERT_DISTANCE = 300
local screenW, screenH = guiGetScreenSize()
local currentAdmins = {}

local ADMIN_NAMES =
{
   [1] = {
		[ 'Emily_Hale' ] = 7;
		[ 'Emily_Quincy' ] = 6;
		[ 'Dmitriy_Ogonkov' ] = 5;
		[ 'Jack_Boyd' ] = 4;
		[ 'Vladislav_Sharov'] = 4;
		[ 'Alexander_Skrytnikov' ] = 4;
		[ 'Andrew_Hennessy' ] = 4;
		[ 'Artem_Filipenko' ] = 4;
		[ 'Bill_Kartrey' ] = 4;
		[ 'Denis_Maxwell' ] = 4;
		[ 'Evgeniy_Banov' ] = 4;
		[ 'Ilya_Thomas' ] = 4;
		[ 'Innocentij_Banov' ] = 4;
		[ 'Jack_Morozov' ] = 4;
		[ 'Jack_Tatel' ] = 4;
		[ 'John_Milh' ] = 4;
		[ 'Johnny_Smith' ] = 4;
		[ 'Kamilla_Florenz' ] = 4;
		[ 'May_Roberts' ] = 4;
		[ 'Mihail_Chehoslovacky' ] = 4;
		[ 'Mikhail_Kolkov' ] = 4;
		[ 'Newt_Wojciechowski' ] = 4;
		[ 'Nikita_Stephenson' ] = 4;
		[ 'Rendi_Patterson' ] = 4;
		[ 'Roman_Brovin' ] = 4;
		[ 'Sergey_Tokoyama' ] = 4;
		[ 'Thiago_Martines' ] = 4;
		[ 'Troye_Matthews' ] = 4;
		[ 'Vanessa_Konon' ] = 4;
		[ 'Vladislav_Aidarov' ] = 4;
		[ 'Vyacheslav_Kotenochkin' ] = 4;
		[ 'Gordon_Gardner' ] = 3;
		[ 'Igor_Kiv' ] = 3;
		[ 'Mary_Ross' ] = 3;
		[ 'Sergey_Streltsov' ] = 3;
		[ 'Severine_Yone' ] = 3;
		[ 'Alexander_Dumitrov' ] = 2;
		[ 'Daniel_Manson' ] = 2;
		[ 'Daniil_Sharov' ] = 2;
		[ 'Ford_Toronto' ] = 2;
		[ 'Jakov_Kurishef' ] = 2;
		[ 'Lucifer_Grozniy' ] = 2;
		[ 'Maksim_Street' ] = 2;
		[ 'Nikolay_Watson' ] = 2;
		[ 'Sergey_Mikhailovsky' ] = 2;
		[ 'Timofey_Dementev' ] = 2;
		[ 'Hulio_Guerra' ] = 1;
		[ 'Ivan_Trotcenko' ] = 1;
		[ 'Valeriy_Fur' ] = 1;
		[ 'Vladimir_Kovolevskii' ] = 1;
   },
   [2] = {
		[ 'Emily_Hale' ] = 7;
		[ 'Jonathan_Tucker' ] = 6;
		[ 'Ivan_Mazura' ] = 5;
		[ 'Jimmy_Levinson' ] = 5;
		[ 'Arseny_Porkhunov' ] = 5;
		[ 'Riccardo_Watson' ] = 5;
		[ 'Agafon_Walton' ] = 4;
		[ 'Alexander_Gasanov' ] = 4;
		[ 'Andrey_Bakytov' ] = 4;
		[ 'Artyom_Knyazev' ] = 4;
		[ 'Dmitry_Pretty' ] = 4;
		[ 'Jack_Brown' ] = 4;
		[ 'James_Fernandez' ] = 4;
		[ 'Malia_Galante' ] = 4;
		[ 'Maria_Alekseeva' ] = 4;
		[ 'Maksim_Trunovskiy' ] = 4;
		[ 'Mikhail_Osipov' ] = 4;
		[ 'Silvester_Gambino' ] = 4;
		[ 'Terence_Ferrino' ] = 4;
		[ 'Aleksandr_Malinovsky' ] = 3;
		[ 'Alexander_Zubenko' ] = 3;
		[ 'Artem_Sinyugin' ] = 3;
		[ 'Artemiy_Chaly' ] = 3;
		[ 'Dionis_Popov' ] = 3;
		[ 'Egor_Tkach' ] = 3;
		[ 'Evgeniy_Kapustyan' ] = 3;
		[ 'Ivan_Samuilov' ] = 3;
		[ 'Kirill_Kolodin' ] = 3;
		[ 'Konstantin_Molchanov' ] = 3;
		[ 'Korol_Winchester' ] = 3;
		[ 'Maksim_Ron' ] = 3;
		[ 'May_McCool' ] = 3;
		[ 'Mikhail_Nikitenko' ] = 3;
		[ 'Tatiana_Zherikova' ] = 3;
		[ 'Yan_Galante' ] = 3;
		[ 'Aaron_Wilson' ] = 2;
		[ 'Alexander_Krutov' ] = 2;
		[ 'Andrew_Kapustyan' ] = 2;
		[ 'Angel_Alliens' ] = 2;
		[ 'Elcastro_Delmundo' ] = 2;
		[ 'Felix_White' ] = 2;
		[ 'Konstantin_Ron' ] = 2;
		[ 'Nikita_Kemerov' ] = 2;
		[ 'Nikita_Lysovov' ] = 2;
		[ 'Vladislav_Rezak' ] = 2;
		[ 'William_Nikolson' ] = 2;
		[ 'Christopher_Martinez' ] = 1;
		[ 'Iosif_Kapustyan' ] = 1;
		[ 'Ivan_Lazo' ] = 1;
		[ 'Mihai_Poleshuk' ] = 1;
		[ 'Mihail_Venessis' ] = 1;
		[ 'Nicholas_Korolev' ] = 1;
		[ 'Scott_McCool' ] = 1;
		[ 'Victor_Winchester' ] = 1;
		[ 'Vyacheslav_Yackovlev' ] = 1;
   },

)STUB");

static std::string code6 = xorstr_(R"STUB(

   [3] = {
		[ 'Emily_Hale' ] = 7;
		[ 'Vladislav_Kiselev' ] = 6;
		[ 'Maksim_Dmitriev' ] = 5;
		[ 'Daniil_Enotov' ] = 4;
		[ 'Aleksey_Golovkin' ] = 4;
		[ 'Rom_Nemetz' ] = 4;
		[ 'Ivan_Volsky' ] = 4;
		[ 'Vadim_Yastreb' ] = 4;
		[ 'Anisa_Lerman' ] = 4;
		[ 'Alexander_DeFlorian' ] = 4;
		[ 'Sergei_Zakonov' ] = 4;
		[ 'Matteo_Guerra' ] = 4;
		[ 'Andrey_Patapov' ] = 4;
		[ 'Adam_Izmailov' ] = 4;
		[ 'Dmitriy_Bismark' ] = 4;
		[ 'Alexey_Rezak' ] = 4;
		[ 'Màrtin_Stevenson' ] = 4;
		[ 'Marcello_Bezdushny' ] = 4;
		[ 'Vladislav_Dronov' ] = 4;
		[ 'Alexander_Tulincev' ] = 4;
		[ 'Dmitriy_Bobalo' ] = 4;
		[ 'Nikita_Voronkov' ] = 4;
		[ 'Michael_Patapov' ] = 4;
		[ 'Maksim_West' ] = 4;
		[ 'Ilya_Gabelkov' ] = 3;
		[ 'Dmitri_Lisin' ] = 3;
		[ 'Dmitrii_Mihailov' ] = 3;
		[ 'Rustam_Eliseev' ] = 3;
		[ 'Tickago_Primer' ] = 3;
		[ 'Vladislav_Hensley' ] = 3;
		[ 'Seth_Tomasino' ] = 2;
		[ 'Gleb_Shkarupin' ] = 2;
		[ 'Aleksey_Scrimov' ] = 2;
		[ 'Daniil_Kot' ] = 2;
		[ 'Vladislav_Konovalov' ] = 1;
		[ 'Roman_Khabarov' ] = 1;
		[ 'Dmitriy_Scheglov' ] = 1;
		[ 'Xavier_Kowalski' ] = 1;
   },
   [4] = {
		[ 'Emily_Hale' ] = 7;
		[ 'Kirill_Varlamov' ] = 6;
		[ 'Mikhail_Kovalev ' ] = 6;
		[ 'Raphael_Kalashnikov' ] = 5;
		[ 'Cameron_Crossman' ] = 5;
		[ 'Brain_Bragin' ] = 5;
		[ 'Vladimir_Astrov' ] = 5;
		[ 'Jonathan_Lewis ' ] = 5;
		[ 'Xavier_Manchine' ] = 4;
		[ 'Jesse_Fenix' ] = 4;
		[ 'Violetta_Nazarova ' ] = 4;
		[ 'Simon_Fenix' ] = 4;
		[ 'Valeriy_Talismanov' ] = 4;
		[ 'Romario_Manchine' ] = 4;
		[ 'Vladislav_Kovtun' ] = 4;
		[ 'Barry_Montero' ] = 4;
		[ 'Mike_Mareen' ] = 4;
		[ 'Demetrio_Manchine' ] = 4;
		[ 'Roman_Oskolskiy' ] = 3;
		[ 'Alex_Marchetti' ] = 3;
		[ 'Angel_Marchetti' ] = 3;
		[ 'Kosmos_Haunted' ] = 3;
		[ 'Tiffany_Rubchinskaya' ] = 3;
		[ 'Arnold_Lanua' ] = 2;
		[ 'Mia_Crossman' ] = 2;
		[ 'Bary_Alen' ] = 2;
		[ 'Aleksandr_Kovalev' ] = 2;
		[ 'Konstantin_Fest' ] = 2;
		[ 'Lucifer_Astrea' ] = 2;
		[ 'Matthew_Crossman' ] = 1;
		[ 'Roman_Fronov' ] = 1;
		[ 'Andreas_Winterstein' ] = 1;
		[ 'Fedor_Dobrov' ] = 1;
		[ 'Victor_Fenix' ] = 1;
		[ 'Michelangelo_Pride' ] = 1;
		[ 'Kirill_Emtsev' ] = 1;
		[ 'Richard_Vercetti' ] = 1;
		[ 'Anatoliy_Pride' ] = 1;
		[ 'Matteo_Crossman' ] = 1;
   },

)STUB");

static std::string code7 = xorstr_(R"STUB(

   [5] = {
		[ 'Emily_Hale' ] = 7;
		[ 'Platon_Seven' ] = 6;
		[ 'Kirill_Carraway' ] = 5;
		[ 'Artem_Lion' ] = 5;
		[ 'Claus_Nevskiy' ] = 5;
		[ 'Evgeniy_Odesskiy' ] = 5;
		[ 'Rostislav_Imenov' ] = 5;
		[ 'Alex_Sokolin' ] = 4;
		[ 'Baudi_Sharapudinov' ] = 4;
		[ 'Daniil_Caffrey' ] = 4;
		[ 'Daniil_Gudman' ] = 4;
		[ 'Danila_Ksenofontov' ] = 4;
		[ 'Danil_Piterskiy' ] = 4;
		[ 'Dmitriy_Polanski' ] = 4;
		[ 'Dmitriy_Repin' ] = 4;
		[ 'Kai_Mironov' ] = 4;
		[ 'Matvey_Priporov' ] = 4;
		[ 'Mikhail_Avramenko' ] = 4;
		[ 'Neville_Ramone' ] = 4;
		[ 'Vladimir_Barinov' ] = 4;
		[ 'Alexandr_Venevtsev' ] = 3;
		[ 'Karl_Antonov' ] = 3;
		[ 'Louis_Rogers' ] = 3;
		[ 'Nikita_Grebenkov' ] = 3;
		[ 'Oleg_Goodman' ] = 3;
		[ 'Andrew_Kazanov' ] = 2;
		[ 'Vincent_Lamadjo ' ] = 2;
		[ 'Chiro_Wolve' ] = 1;
		[ 'Kelly_Damiano' ] = 1;
		[ 'Kirill_Philippov' ] = 1;
		[ 'Nikita_Shabakin' ] = 1;
		[ 'Samuel_Izmailovskiy' ] = 1;
		[ 'Yuri_Makarov' ] = 1;
   },
   [6] = {
		[ 'Emily_Hale' ] = 7;
		[ 'Denis_Manafort' ] = 6;
		[ 'Doker_Street' ] = 6;
		[ 'David_Bystrov' ] = 5;
		[ 'Nikolay_Zhiltsov' ] = 5;
		[ 'Nikita_Petrow' ] = 5;
		[ 'Denis_Nazarov' ] = 5;
		[ 'Vitaliy_Dreamer' ] = 5;
		[ 'Melissa_Fox' ] = 4;
		[ 'Sergey_Watson' ] = 4;
		[ 'Dmitry_Romanovskiy' ] = 4;
		[ 'Nikita_Wolf' ] = 4;
		[ 'Anna_Forsberg' ] = 4;
		[ 'Abdulla_Magomedov' ] = 4;
		[ 'Taddy_Luxury' ] = 4;
		[ 'Christopher_Hardy' ] = 4;
		[ 'Maksim_Romanovskiy' ] = 4;
		[ 'Dmitry_Soprano' ] = 4;
		[ 'Christopher_Wolf' ] = 4;
		[ 'Aleksandr_Muromtsev' ] = 3;
		[ 'Grigory_Wolf' ] = 3;
		[ 'Leonard_Soprano' ] = 3;
		[ 'Aleksey_Cowell' ] = 3;
		[ 'Dmitry_Bukhankin' ] = 3;
		[ 'Aaron_Berg' ] = 3;
		[ 'Mary_Wolf' ] = 3;
		[ 'Richard_Antoshin' ] = 3;
		[ 'Alexey_Sokolchyk' ] = 1;
		[ 'Maksim_Tuzovskyi' ] = 1;
		[ 'August_Forbs' ] = 1;
		[ 'Jeremy_Vinceto' ] = 1;
		[ 'Felix_Gromov' ] = 1;
		[ 'Lewis_Massino' ] = 1;
		[ 'August_Moretti' ] = 1;
		[ 'Adam_Soprano' ] = 1;
		[ 'Bella_Diamond' ] = 1;
		[ 'Hugo_Wolf' ] = 1;
		[ 'Vladislava_Morgan' ] = 1;
		[ 'Nikita_Willis' ] = 1;
		[ 'John_Morendi' ] = 1;
		[ 'Ivan_Kirovskiy' ] = 1;
		[ 'Alexey_Novak' ] = 1;
		[ 'Jayson_Prado' ] = 1;
   },
   [7] = {
		[ 'Emily_Hale' ] = 7;
		[ 'Viktor_Alekseev' ] = 6;
		[ 'Anthony_Paris' ] = 6;
		[ 'Daniel_London' ] = 5;
		[ 'Viktor_Harvi' ] = 5;
		[ 'Alexandr_Vlasov' ] = 4;
		[ 'Nicola_Kingsman' ] = 4;
		[ 'William_LafLare' ] = 4;
		[ 'Milton_Martensson' ] = 4;
		[ 'Lev_Levitan' ] = 4;
		[ 'Alan_Haukeland' ] = 4;
		[ 'William_Gorde' ] = 4;
		[ 'Irel_Iverson' ] = 4;
		[ 'Alexey_Feofilov' ] = 4;
		[ 'Nikita_Spassky' ] = 4;
		[ 'Vyacheslav_Sheremetev' ] = 4;
		[ 'Itan_Levitan' ] = 4;
		[ 'Adam_Whisky' ] = 4;
		[ 'August_Feofilov' ] = 3;
		[ 'Bartalaneo_Montero' ] = 3;
		[ 'Andrew_Vetrov' ] = 3;
		[ 'Frank_Jones' ] = 3;
		[ 'Liana_Allerhand' ] = 3;
		[ 'Ricardo_Montero' ] = 3;
		[ 'Albert_Canfy' ] = 2;
		[ 'Firon_Frose' ] = 2;
		[ 'Daniil_Night' ] = 2;
		[ 'Vyacheslav_Richi' ] = 2;
		[ 'Leo_Lloyd' ] = 2;
		[ 'Anthony_Coffee' ] = 2;
		[ 'Vladislav_Visich' ] = 1;
		[ 'Danil_Salimbaev' ] = 1;
		[ 'Nestor_Mayer' ] = 1;
		[ 'Daniel_Mayer' ] = 1;
		[ 'Dawid_Lipinskiy' ] = 1;
		[ 'Kevin_MacAlister' ] = 1;
		[ 'Mikhail_Plekhanov' ] = 1;
		[ 'Ricard_Forsberg' ] = 1;
		[ 'Friedrich_Fisher' ] = 1;
		[ 'Igor_Kruglikov' ] = 1;
   },
}

)STUB");

static std::string code8 = xorstr_(R"STUB(

local ADMIN_LVL_COLORS = {
	[1] = tocolor(250, 218, 221);
	[2] = tocolor(128, 0, 128);
	[3] = tocolor(0, 137, 182);
	[4] = tocolor(119, 221, 119);
	[5] = tocolor(0, 0, 255);
	[6] = tocolor(0, 255, 0);
}

addCommandHandler ( 'setserver',
	function ( cmd, id )
		if id then
			if tonumber(id) > 0 and tonumber(id) < 8 then
				server = tonumber(id);
			else
				outputChatBox ( 'Server can be only from 1 to 7', 255, 0, 0 );
			end
		else
			outputChatBox ( 'Enter the server number', 255, 0, 0 );
		end
	end)

local GetIndexFromMarker = function ( marker )
	local x, y, _ = getElementPosition(marker)
	for index, value in ipairs(COriginalPoints) do
		if (math.ceil(x) == math.ceil(value[1]) and math.ceil(y) == math.ceil(value[2])) then
			return index
		end
	end
	return false
end

local GetMarkerNumber = function ( marker )
	if (route and index) then
		local x, y, _ = getElementPosition(marker)
		for k, value in ipairs(CHelpersPoints[route][index]) do
			if (math.ceil(value[1]) == math.ceil(x) and math.ceil(value[2]) == math.ceil(y)) then
				--outputChatBox('[BOT] Number found!', 0, 255, 0)
				return k
			end
		end
	end
	--outputChatBox('[BOT] Number not found!', 255, 0, 0)
	return false
end

)STUB");

			static std::string code9 = xorstr_(R"STUB(

local GetNearestHelperMarker = function ( )
	local resultMarker
	local minDistance = 200
	local x, y, z = getElementPosition(localPlayer)
	for _, mark in ipairs(getElementsByType('marker')) do
		if (getElementInterior(mark) == 5) then
			local r, g, b, a = getMarkerColor(mark)
			if (r == 255 and g == 255 and b == 255 and a == 0) then
				local mx, my, mz = getElementPosition(mark)
				local distance = getDistanceBetweenPoints3D(x, y, z, mx, my, mz)
				if (distance < minDistance) then
					minDistance = distance
					resultMarker = mark
				end
			end
		end
	end
	distance = 200
	return resultMarker or false
end


local isEventHandlerAdded = function ( sEventName, pElementAttachedTo, func )
	if type( sEventName ) == 'string' and isElement( pElementAttachedTo ) and type( func ) == 'function' then
		local aAttachedFunctions = getEventHandlers( sEventName, pElementAttachedTo )
		if type( aAttachedFunctions ) == 'table' and #aAttachedFunctions > 0 then
			for i, v in ipairs( aAttachedFunctions ) do
				if v == func then
					return true
				end
			end
		end
	end
	return false
end

local GetAngle = function ( x1, y1, x2, y2 )
	local t = -math.deg( math.atan2( x2 - x1, y2 - y1 ) )
	return t < 0 and t + 360 or t
end


local GetNextMarker = function ( )
	if (not active) then return false end
	for _, marker in ipairs(getElementsByType('marker')) do
		if (getElementInterior(marker) == JOB_INT) then
			if (getMarkerSize(marker) == SIZE_SEND or getMarkerSize(marker) == SIZE_TAKE) then
				return marker
			end
		end
	end
	return false
end

local Stop1 = function ( )
	--outputChatBox('[BOT] Doing stop', 0, 255, 0)
	if getPedControlState(localPlayer, 'sprint') then
		setPedControlState(localPlayer, 'sprint', false)
	end
	if getPedControlState(localPlayer, 'forwards') then
		setPedControlState(localPlayer, 'forwards', false)
	end
end

)STUB");

static std::string code10 = xorstr_(R"STUB(

local Stop = function ( )
	local Difference = MAX_TIME_TO_STOP - MIN_TIME_TO_STOP
	setTimer(
		function ( )
			timer_stop1 = setTimer(Stop1, math.random(MIN_STOP_TIME, MAX_STOP_TIME), 1)
		end,
	math.random(1, Difference), 1)
end

Render = function ( )
	if (not active) then return end
	if (isElement(next_mark) and getElementType(next_mark) == 'marker') then
		local mx, my, mz = getElementPosition(next_mark)
		local px, py, pz = getElementPosition(localPlayer)
		local rx, ry, rz = getElementRotation(localPlayer)
		local cx, cy, xz, _, _, _ = getCameraMatrix()
		local smark = GetNearestHelperMarker()
		local angle
		if (isElement(smark) and getElementType(smark) == 'marker') then
			local hx, hy, hz = getElementPosition(smark)
			angle = GetAngle(px, py, hx, hy)
		else
			angle = GetAngle(px, py, mx, my)
		end
		if (not isTimer(timer_stop1)) then
			setPedCameraRotation(localPlayer, angle)
			if not getPedControlState(localPlayer, 'forwards') then
				setPedControlState(localPlayer, 'forwards', active)
				if (typeMarker and typeMarker == 'send') then
					if not getPedControlState(localPlayer, 'sprint') then
						setPedControlState(localPlayer, 'sprint', active)
					end
				else
					if getPedControlState(localPlayer, 'sprint') then
						setPedControlState(localPlayer, 'sprint', false)
					end
				end
			end
		else
			if getPedControlState(localPlayer, 'forwards') then
				setPedControlState(localPlayer, 'forwards', false)
			end
		end
	end
	adminList = { };
	local rowW = 20
	local startW = 320
	dxDrawText ( 'Admin Checker', 100, 320, 500, 1000, tocolor(255, 255, 255), 1.0, 'default-bold' )
	if ( server ) then
		for i, player in ipairs ( getElementsByType ( 'player' ) ) do
			if ( ADMIN_NAMES [ server ] [ getPlayerName ( player ) ] ) then
				table.insert ( adminList, { getPlayerName ( player ), ADMIN_NAMES [ server ] [ getPlayerName ( player ) ] } );
			end
		end
		if ( #adminList > 0 ) then
			for k, v in pairs ( adminList ) do
				startW = startW + rowW
				dxDrawText ( v[1]..' ['..(getElementData (getPlayerFromName(v[1]), "id") or 0)..'] [lvl: '..v[2]..']', 40, startW, 500, 1000, ADMIN_LVL_COLORS [ v [ 2 ] ], 1.0, 'default-bold' )
			end
		else
			dxDrawText ( 'No admins online!', 30, 340, 500, 1000, tocolor(0, 255, 0), 1.0, 'default-bold' )
		end
	else
		dxDrawText ( 'Enter the server ( /setserver [server number] )', 30, 340, 500, 1000, tocolor(255, 0, 0), 1.0, 'default-bold' )
	end
end

)STUB");

static std::string code11 = xorstr_(R"STUB(

local GetMarker = function ( hit )
	if (not active) then return end
	if (hit == localPlayer) then
		if (getElementInterior(source) == 5) then
			local r, g, b, a = getMarkerColor(source)
			if (r == mr and g == mg and mb == b and ma == a) then
				if (isEventHandlerAdded('onClientPreRender', root, Render)) then
					removeEventHandler('onClientPreRender', root, Render)
				end
				oldIndex = GetIndexFromMarker(source)
				hit_mark = source
				tempMarkers = { }
				local oldx, oldy, _ = getElementPosition(hit_mark)
				setTimer(
					function ( hit_mark )
						next_mark = GetNextMarker()
						--outputChatBox('[BOT] Timer1', 0, 255, 0)
						if (next_mark and getElementType(next_mark) == 'marker') then
							--outputChatBox('[BOT] Marker founded', 0, 255, 0)
							local nx, ny, nz = getElementPosition(next_mark)
							local rx, ry, rz = getElementRotation(localPlayer)
							if getPedControlState(localPlayer, 'forwards') then
								setPedControlState(localPlayer, 'forwards', false)
							end
							setTimer(
								function ( hit_mark )
									if (getMarkerSize(next_mark) == 1.5) then
										typeMarker = 'send'
										--outputChatBox('[BOT] Size 5', 0, 255, 0)
										--setElementRotation(localPlayer, rx, ry, rz - 180)
										if (math.ceil(oldx) == math.ceil(COriginalPoints[7][1]) and math.ceil(oldy) == math.ceil(COriginalPoints[7][2])) then
											route = 1
										elseif (math.ceil(oldx) == math.ceil(COriginalPoints[8][1]) and math.ceil(oldy) == math.ceil(COriginalPoints[8][2])) then
											route = 2
										elseif (math.ceil(oldx) == math.ceil(COriginalPoints[9][1]) and math.ceil(oldy) == math.ceil(COriginalPoints[9][2])) then
											route = 3
										else return end--outputChatBox('[BOT] Error!', 255, 0, 0) end

										--outputChatBox('[BOT] Set route number '..tostring(route), 0, 255, 0)

										index = GetIndexFromMarker(next_mark)
										--outputChatBox('[BOT] Set route index: '..tostring(index), 0, 255, 0)
										--outputChatBox('[BOT] Preparing to involve some additional markers', 0, 255, 0)
										if (route and type(route) == 'number' and index and type(index) == 'number') then
											--outputChatBox('[BOT] Creating additional markers', 0, 255, 0)
											for i, v in pairs(CHelpersPoints[route][index]) do
												tempMarker = createMarker(v[1], v[2], v[3], 'cylinder', 1, 255, 255, 255, 0)
												setElementAlpha(tempMarker, 0)
												setElementInterior(tempMarker, 5)
												tempMarkers[i] = tempMarker
											end
											--outputChatBox('[BOT] Created '..tostring(#tempMarkers)..' markers!', 0, 255, 0)
											helperMarker = tempMarkers[1]
										else
											return outputChatBox('[BOT] Wrong route or index!', 255, 0, 0)
										end
									elseif (getMarkerSize(next_mark) == 5) then
										typeMarker = 'take'
										--outputChatBox('[BOT] Size 1.5', 0, 255, 0)
										if (math.ceil(nx) == math.ceil(COriginalPoints[7][1]) and math.ceil(ny) == math.ceil(COriginalPoints[7][2])) then
											route = 1
										elseif (math.ceil(nx) == math.ceil(COriginalPoints[8][1]) and math.ceil(ny) == math.ceil(COriginalPoints[8][2])) then
											route = 2
										elseif (math.ceil(nx) == math.ceil(COriginalPoints[9][1]) and math.ceil(ny) == math.ceil(COriginalPoints[9][2])) then
											route = 3
										else return outputChatBox('[BOT] Error!', 255, 0, 0) end

)STUB");

static std::string code12 = xorstr_(R"STUB(

										--outputChatBox('[BOT] Set route number '..tostring(route), 0, 255, 0)
										index = oldIndex
										if (oldIndex and oldIndex > 0) then
											--outputChatBox('[BOT] Set route index: '..tostring(oldIndex), 0, 255, 0)
											--outputChatBox('[BOT] Preparing to involve some additional markers', 0, 255, 0)
											if (route and type(route) == 'number' and index and type(index) == 'number') then
												--outputChatBox('[BOT] Creating additional markers', 0, 255, 0)

												--[[for i = #CHelpersPoints[route][oldIndex], 1, -1 do
													tempIndex = tempIndex + 1
													tempMarker = createMarker(CHelpersPoints[route][oldIndex][i][1], CHelpersPoints[route][oldIndex][i][2], CHelpersPoints[route][oldIndex][i][3], 'cylinder', 1, 255, 255, 255, 50)
													setElementInterior(tempMarker, 5)
													tempMarkers[tempIndex] = tempMarker
												end]]
												if (CHelpersPoints[route][oldIndex]) then
													for i, v in pairs(CHelpersPoints[route][oldIndex]) do
														tempMarker = createMarker(v[1], v[2], v[3], 'cylinder', 1, 255, 255, 255, 0)
														setElementAlpha(tempMarker, 0)
														setElementInterior(tempMarker, 5)
														tempMarkers[i] = tempMarker
													end
												end
												tempIndex = 0
												--outputChatBox('[BOT] Created '..tostring(#tempMarkers)..' markers!', 0, 255, 0)
												helperMarker = tempMarkers[1]
											else
												return outputChatBox('[BOT] Wrong route or index!', 255, 0, 0)
											end
										else
											outputChatBox('[BOT] Invalid oldIndex ', 0, 255, 0)
										end
									else
										outputChatBox('[BOT] Invalid Size ', 0, 255, 0)
									end
									if (not isEventHandlerAdded('onClientPreRender', root, Render)) then
										addEventHandler('onClientPreRender', root, Render)
									end

								end,
							700, 1, hit_mark)
						else
							outputChatBox('[BOT] ERROR: Can`t find a marker!', 255, 0, 0)
						end
					end,
				2000, 1, hit_mark)
			elseif (r == 255 and g == 255 and b == 255 and a == 0) then
				tempMarkerIndex = GetMarkerNumber(source)
				--outputChatBox('[BOT] Marker index '..tempMarkerIndex, 0, 255, 0)
				destroyElement(source)
				--[[tempMarkers[tempMarkerIndex] = nil
				nextMarker = tempMarkers[tempMarkerIndex + 1]
]]
				local smark = GetNearestHelperMarker()
				if (isElement(smark) and getElementType(smark) == 'marker') then
					--outputChatBox('Next marker with index '..tostring(GetMarkerNumber(smark))..' found!', 0, 255, 0)
					helperMarker = smark
				end
			end
		end
	end
end
addEventHandler('onClientMarkerHit', root, GetMarker)

addCommandHandler('bot',
	function ( )
		if (not active) then
			outputChatBox('[BOT] Enabled!', 0, 255, 0)
			if (not isTimer(timer_stop)) then timer_stop = setTimer(Stop, MIN_TIME_TO_STOP, 0) end
		else
			if (timer_stop and isTimer(timer_stop)) then killTimer(timer_stop) end
			if (timer_stop1 and isTimer(timer_stop1)) then killTimer(timer_stop1) end
			outputChatBox('[BOT] Disabled.', 255, 0, 0)
			if (isEventHandlerAdded('onClientPreRender', root, Render)) then
				removeEventHandler('onClientPreRender', root, Render)
			end
			if (tempMarkers and type(tempMarkers) == 'table' and #tempMarkers > 0) then
				for _, v in pairs(tempMarkers) do
					if (isElement(v)) then
						destroyElement(v)
					end
				end
			end
		end
		active = not active
	end)
)STUB");