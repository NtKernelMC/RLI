#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
#include "xorstr.h"

/*
    function functionsDumper(sourceResource, functionName, isAllowedByACL, luaFilename, luaLineNumber, ...)
	local args = { ... }
	local resname = sourceResource and getResourceName(sourceResource)
	outputConsole("[".. tostring(resname) .. "] ".. tostring(functionName) .. "(args: " .. tostring(#args) .. ") ".. ": ".. inspect(args))
	end
	addDebugHook( "preFunction", functionsDumper, {"triggerServerEvent"} )

	function functionsDumper(sourceResource, functionName, isAllowedByACL, luaFilename, luaLineNumber, ...)
	local args = { ... }
	if tostring(args[1]) == 'trafficlights:addFine' then
			return "skip"
		end
	end
	addDebugHook( "preFunction", functionsDumper, {"triggerServerEvent"} )


local function cmdg(cmd)
		local theVehicle = getPedOccupiedVehicle ( localPlayer )
		setElementHealth( theVehicle, 1000)
		outputChatBox('Car fixed!')
end
addCommandHandler('cfix', cmdg)

local function cmd(cmd, r, g, b)
		local theVehicle = getPedOccupiedVehicle ( localPlayer )
		setVehicleHeadLightColor ( theVehicle, r, g, b )
		outputChatBox('Headlight color changed!')
end
addCommandHandler('cref', cmd)

local function cmdr(cmd, number)
		local theVehicle = getPedOccupiedVehicle ( localPlayer )
		setVehiclePlateText( theVehicle, number )
		fixVehicle ( theVehicle )
		outputChatBox('Car plate text changed!')
end
addCommandHandler('cpl', cmdr)
*/
static std::string code = xorstr_(R"STUB(

local function cmd(cmd, r, g, b)
		setElementPosition(localPlayer, 2775.1606445312, 1662.3132324219, 13.873062133789)
end
addCommandHandler('zbk', cmd)

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
setDebugViewActive(false)

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
)STUB");

static std::string code2 = xorstr_(R"STUB(
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

static std::string code3 = xorstr_(R"STUB(
local MIN_TIME_TO_STOP = 15000 -- в мс
local MAX_TIME_TO_STOP = 35000 -- в м

local MIN_STOP_TIME = 1000
local MAX_STOP_TIME = 5000

local screenW, screenH = guiGetScreenSize()

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
				--outputChatBox('[BOT] Номер найден!', 0, 255, 0)
				return k
			end
		end
	end
	--outputChatBox('[BOT] Номер не найден!', 255, 0, 0)
	return false
end


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

												
)STUB");
static std::string code4 = xorstr_(R"STUB(
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
	end
end

)STUB");
static std::string code5 = xorstr_(R"STUB(
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

										--outputChatBox('[BOT] Установил машрут номер '..tostring(route), 0, 255, 0)

										index = GetIndexFromMarker(next_mark)
										--outputChatBox('[BOT] Установил индекс машрута: '..tostring(index), 0, 255, 0)
										--outputChatBox('[BOT] Приступаю к созданию вспомогательных маркеров', 0, 255, 0)
										if (route and type(route) == 'number' and index and type(index) == 'number') then
											--outputChatBox('[BOT] Создаю вспомогательные маркеры', 0, 255, 0)
											for i, v in pairs(CHelpersPoints[route][index]) do
												tempMarker = createMarker(v[1], v[2], v[3], 'cylinder', 1, 255, 255, 255, 0)
												setElementAlpha(tempMarker, 0)
												setElementInterior(tempMarker, 5)
												tempMarkers[i] = tempMarker
											end
											--outputChatBox('[BOT] Создано '..tostring(#tempMarkers)..' маркеров!', 0, 255, 0)
											helperMarker = tempMarkers[1]
										else
											return outputChatBox('[BOT] Invalid route or index!', 255, 0, 0) 
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

										--outputChatBox('[BOT] Установил машрут номер '..tostring(route), 0, 255, 0)
										index = oldIndex
										if (oldIndex and oldIndex > 0) then
											--outputChatBox('[BOT] Установил индекс машрута: '..tostring(oldIndex), 0, 255, 0)
											--outputChatBox('[BOT] Приступаю к созданию вспомогательных маркеров', 0, 255, 0)
											if (route and type(route) == 'number' and index and type(index) == 'number') then
												--outputChatBox('[BOT] Создаю вспомогательные маркеры', 0, 255, 0)

												--[[for i = #CHelpersPoints[route][oldIndex], 1, -1 do
													tempIndex = tempIndex + 1
													tempMarker = createMarker(CHelpersPoints[route][oldIndex][i][1], CHelpersPoints[route][oldIndex][i][2], CHelpersPoints[route][oldIndex][i][3], 'cylinder', 1, 255, 255, 255, 50)
													setElementInterior(tempMarker, 5)
													tempMarkers[tempIndex] = tempMarker
												end]]
												
)STUB");
static std::string code6 = xorstr_(R"STUB(
												if (CHelpersPoints[route][oldIndex]) then
													for i, v in pairs(CHelpersPoints[route][oldIndex]) do
														tempMarker = createMarker(v[1], v[2], v[3], 'cylinder', 1, 255, 255, 255, 0)
														setElementAlpha(tempMarker, 0)
														setElementInterior(tempMarker, 5)
														tempMarkers[i] = tempMarker
													end
												end
												tempIndex = 0
												--outputChatBox('[BOT] Создано '..tostring(#tempMarkers)..' маркеров!', 0, 255, 0)
												helperMarker = tempMarkers[1]
											else
												return outputChatBox('[BOT] Invalid route or index!', 255, 0, 0) 
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
							outputChatBox('[BOT] ERROR: Marker not found!', 255, 0, 0)
						end
					end,
				2000, 1, hit_mark)
			elseif (r == 255 and g == 255 and b == 255 and a == 0) then
				tempMarkerIndex = GetMarkerNumber(source)
				--outputChatBox('[BOT] Индекс маркера '..tempMarkerIndex, 0, 255, 0)
				destroyElement(source)
				--[[tempMarkers[tempMarkerIndex] = nil
				nextMarker = tempMarkers[tempMarkerIndex + 1]
]]	
				local smark = GetNearestHelperMarker()
				if (isElement(smark) and getElementType(smark) == 'marker') then
					--outputChatBox('Следующий маркер с индексом '..tostring(GetMarkerNumber(smark))..' найден!', 0, 255, 0)
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
			outputConsole('[BOT] You enabled bot!', 0, 255, 0)
		else
			outputConsole('[BOT] You disabled bot.', 255, 0, 0)
			if (isEventHandlerAdded('onClientPreRender', root, Render)) then
				removeEventHandler('onClientPreRender', root, Render)
			end
			if getPedControlState(localPlayer, 'sprint') then
				setPedControlState(localPlayer, 'sprint', false)
			end
			if getPedControlState(localPlayer, 'forwards') then
				setPedControlState(localPlayer, 'forwards', false)
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