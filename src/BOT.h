#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
#include "xorstr.h"

static std::string code = xorstr_(R"STUB(local PARSE_INTERVAL = 3000
local ALERT_DISTANCE = 300
local screenW, screenH = guiGetScreenSize()
local currentAdmins = {}

)STUB");

static std::string code2 = xorstr_(R"STUB(

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

)STUB");

static std::string code3 = xorstr_(R"STUB(

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

static std::string code4 = xorstr_(R"STUB(

	local ADMIN_LVL_COLORS = {
   [1] = tocolor(250, 218, 221);
   [2] = tocolor(128, 0, 128);
   [3] = tocolor(0, 137, 182);
   [4] = tocolor(119, 221, 119);
   [5] = tocolor(0, 0, 255);
   [6] = tocolor(0, 255, 0);
}

function showAdminList( )
   adminList = { };
   local rowW = 20
   local startW = 320
   dxDrawText ( 'Admin Checker', 1200, 320, 500, 1000, tocolor(255, 255, 255), 1.0, 'default-bold' )
   if ( server ) then
      for i, player in ipairs ( getElementsByType ( 'player' ) ) do
         if ( ADMIN_NAMES [ server ] [ getPlayerName ( player ) ] ) then
            table.insert ( adminList, { getPlayerName ( player ), ADMIN_NAMES [ server ] [ getPlayerName ( player ) ] } );
         end
      end
      if ( #adminList > 0 ) then
         for k, v in pairs ( adminList ) do
            startW = startW + rowW
            dxDrawText ( v[1]..' ['..(getElementData (getPlayerFromName(v[1]), "id") or 0)..'] [lvl: '..v[2]..']', 1140, startW, 500, 1000, ADMIN_LVL_COLORS [ v [ 2 ] ], 1.0, 'default-bold' )
         end
      else
         dxDrawText ( 'There is no admins online!', 1170, 340, 500, 1000, tocolor(0, 255, 0), 1.0, 'default-bold' )
      end
   else
      dxDrawText ( 'Enter the server ( /setserver [server number] )', 1100, 340, 500, 1000, tocolor(255, 0, 0), 1.0, 'default-bold' )
   end
end
addEventHandler('onClientRender', root, showAdminList)

addCommandHandler ( 'setserver',
      function ( cmd, id )
         if id then
            if tonumber(id) > 0 and tonumber(id) < 8 then
               server = tonumber(id);
            else
               outputChatBox ( 'The server number can be only from 1 to 7!', 255, 0, 0 );
            end
         else
            outputChatBox ( 'Please, enter the server number!', 255, 0, 0 );
         end
      end)
)STUB");