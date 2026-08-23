#include "Scene.h"
#include "IOSystem.h"
#include "RenderManager.h"
#include "NavMeshSystem.h"
#include "prefabs.h"
#include "TextureManager.h"
#include "BotLogic.h"
#include "Random.h"
#include "MaterialManager.h"
#include "HouseGenerator.h"
#include "ClientServerSystem.h"
#include "Settings.h"
#include "GameplayGenerator.h"
#include "InventoryManager.h"

void createMainSimulation() {
	Object cube = ECS::createObject();
	cube.transform.scale = 0.2;
	cube.AddComponent<RenderView>().mesh_index = MESH_Sphere;
	cube.GetComponent<RenderView>().materals[0] = PrefabSystem::getInstance().FloortexMaterial;

	for(int i = 0; i < 5; i++) {
		PrefabSystem::getInstance().createCapsule().transform.position = Vector3(22 + i * 3, 15, 62);
	}

	float startPos = -14;
	Object axe = PrefabSystem::getInstance().createAxe();
	axe.transform.position = Vector3(startPos++, 1, 10);
	axe.transform.rotation = Quaternion::FromEuler(0, -180, 0);

	Object ball = PrefabSystem::getInstance().createBall();
	ball.transform.position = Vector3(startPos++, 1, 10);

	PrefabSystem::getInstance().createBoards( Vector3(startPos++, 1, 10), Quaternion::FromEuler(0, -90, 0));
	startPos++;
	
	Object bed = PrefabSystem::getInstance().createBed();
	bed.transform.position = Vector3(startPos++, 0, 10);
	bed.transform.rotation = Quaternion::FromEuler(0, -180, 0);

	Object battary = PrefabSystem::getInstance().createBattery();
	battary.transform.position = Vector3(startPos++, 1, 10);

	Object bolt = PrefabSystem::getInstance().createBolt();
	bolt.transform.position = Vector3(startPos++, 1, 10);

	Object bookshelf = PrefabSystem::getInstance().createBookshelf();
	bookshelf.transform.position = Vector3(startPos++, 0, 10);
	bookshelf.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	Object bookshelf2 = PrefabSystem::getInstance().createBookshelf2();
	bookshelf2.transform.position = Vector3(startPos++, 0, 10);
	bookshelf2.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	Object bookshelf3 = PrefabSystem::getInstance().createBookshelf3();
	bookshelf3.transform.position = Vector3(startPos++, 0, 10);
	bookshelf3.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	Object bookshelf4 = PrefabSystem::getInstance().createBookshelf4();
	bookshelf4.transform.position = Vector3(startPos++, 0, 10);
	bookshelf4.transform.rotation = Quaternion::FromEuler(0, 90, 0);
		
	Object box = PrefabSystem::getInstance().createBox();
	box.transform.position = Vector3(startPos++, 1, 10);

	Object bucket = PrefabSystem::getInstance().createBucket();
	bucket.transform.position = Vector3(startPos++, 1, 10);

	Object catVase = PrefabSystem::getInstance().createCatVase();
	catVase.transform.position = Vector3(startPos++, 1, 10);
	catVase.transform.rotation = Quaternion::FromEuler(0, -180, 0);

	Object chair = PrefabSystem::getInstance().createChair();
	chair.transform.position = Vector3(startPos++, 1, 10);
	chair.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	Object clock = PrefabSystem::getInstance().createClock();
	clock.transform.position = Vector3(startPos++, 1, 10);
	clock.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	Object coin = PrefabSystem::getInstance().createCoin();
	coin.transform.position = Vector3(startPos++, 1, 10);
	coin.transform.rotation = Quaternion::FromEuler(-90, 0, 0);

	Object computerSystem = PrefabSystem::getInstance().createComputerSystem();
	computerSystem.transform.position = Vector3(startPos++, 1, 10);
	computerSystem.transform.rotation = Quaternion::FromEuler(0, 90, 0);
	startPos++;

	Object cupboard = PrefabSystem::getInstance().createBookshelf5();
	cupboard.transform.position = Vector3(startPos++, 1, 10);
	cupboard.transform.rotation = Quaternion::FromEuler(0, 90, 0);
	startPos++;
	
	Object door = PrefabSystem::getInstance().createDoor();
	door.transform.position = Vector3(startPos++, 0, 10);
	door.transform.rotation = Quaternion::FromEuler(0, 90, 0);
	startPos++;
	
	Object eshield = PrefabSystem::getInstance().createEshield();
	eshield.transform.position = Vector3(startPos++, 1, 10);
	eshield.transform.rotation = Quaternion::FromEuler(0, 90, 0);
	
	Object fireextinguisher = PrefabSystem::getInstance().createFireextinguisher();
	fireextinguisher.transform.position = Vector3(startPos++, 1, 10);
	fireextinguisher.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	Object gasmask = PrefabSystem::getInstance().createGasMask();
	gasmask.transform.position = Vector3(startPos++, 1, 10);
	gasmask.transform.rotation = Quaternion::FromEuler(0, 180, 0);

	Object hammer = PrefabSystem::getInstance().createHammer();
	hammer.transform.position = Vector3(startPos++, 1, 10);
	hammer.transform.rotation = Quaternion::FromEuler(0, 180, 0);

	Object ladder = PrefabSystem::getInstance().createLadder(7);
	ladder.transform.position = Vector3(startPos++, 1, 10);
	ladder.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	Object locker = PrefabSystem::getInstance().createLocker();
	locker.transform.position = Vector3(startPos++, 1, 10);
	locker.transform.rotation = Quaternion::FromEuler(0, 180, 0);

	Object key = PrefabSystem::getInstance().createKey();
	key.transform.position = Vector3(startPos++, 1, 10);
	key.transform.rotation = Quaternion::FromEuler(0, 0, 0);

	Object picture1 = PrefabSystem::getInstance().createPicture(0);
	picture1.transform.position = Vector3(startPos++, 1, 10);
	picture1.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	Object valve = PrefabSystem::getInstance().createValve();
	valve.transform.position = Vector3(startPos++, 1, 10);
	valve.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	Object wardrobe = PrefabSystem::getInstance().createWardrobe();
	wardrobe.transform.position = Vector3(startPos++, 0, 10);
	wardrobe.transform.rotation = Quaternion::FromEuler(0, 90, 0);

	OverlayManager::Create();
	Object player = PrefabSystem::getInstance().createPlayer(true);
	player.GetComponent<CameraControlSystem>().obj = cube;
	player.GetComponent<CameraControlSystem>().Start();
	Object mainCamera = player.getChild(0);

	Object terrain = PrefabSystem::getInstance().createTerrain(0);
	terrain.transform.scale = 4;
	terrain.transform.scale.y = 1;
	terrain.transform.position -= Vector3(50, 0, 50);

	Object text3d = ECS::createObject();
	text3d.transform.scale = 0.2f;
	text3d.transform.position = Vector3(-11, 3.0f, 100);
	text3d.AddComponent<TextView>();
	text3d.GetComponent<TextView>().text = "Sanya is \na super\nmega loser!!!!";
	text3d.GetComponent<TextView>().buildMesh();


	short botMat = MaterialManager::CreateMaterial(Material(SHADER_standartShader, TEX_Axe, 0, 0xff));
	short maskMat = MaterialManager::CreateMaterial(Material(SHADER_standartShader, TEX_Axe, 0, 0xff));
	for (int i = 0; i < -3; i++) {
		Object Bot = ECS::createObject();
		Bot.transform.scale = 1;
		Bot.AddComponent<RenderView>().mesh_index = MESH_Cube;
		Bot.GetComponent<RenderView>().materals[0] = botMat;
		Bot.AddComponent<NavMeshAgent>().speed = 0.01;
		Bot.AddComponent<BotLogic>();

		Object mask = ECS::createObject();
		mask.transform.scale = 1;
		// mask.transform.position = 12;
		mask.AddComponent<RenderView>().mesh_index = 1;
		mask.GetComponent<RenderView>().materals[0] = maskMat;
		mask.setParent(Bot);
	}




	enum Action : int {
		UnlockKey      = 1u << 0,   // открыть ключом
		CutMetal       = 1u << 1,   // резать металл
		UnlockCode     = 1u << 2,   // открыть кодом
		Cut            = 1u << 3,   // резать
		Electric       = 1u << 4,   // работать с электричеством
		Smash          = 1u << 5,   // ломать / пробивать
		Burn           = 1u << 6,   // прожигать
		GasSafe        = 1u << 7,   // защита от газа
		ValveControl   = 1u << 8,   // открыть/закрыть вентиль
		Float          = 1u << 9,   // плавать
		Insulated      = 1u << 10,  // изоляция от тока
		Repair         = 1u << 11,  // чинить
		Unscrew        = 1u << 12,  // откручивать
		Extinguish     = 1u << 13,  // тушить
		PowerOn        = 1u << 14,  // включить питание
		PowerOff       = 1u << 15,  // выключить питание
		Shoot          = 1u << 16,  // стрелять
		Bait           = 1u << 17,  // приманка
		Meat           = 1u << 18,  // мясо
		Hide           = 1u << 19,  // укрыться
		Conductive     = 1u << 20,  // проводящий материал
	};

	const char* solutionNames[] = {
		"Klyuch",
		"Parol",
		"Boltorez",
		"Uglovaya_shlifovalnaya_mashina",
		"Gazorez",
		"Protivogaz",
		"Molotok",
		"Topor",
		"Otvyortka",
		"Klapan",
		"Shiny",
		"Ognetushitel",
		"Sistema_pozharotusheniya",
		"Elektricheskiy_shchit",
		"Pistolet"
	};

	const char* obstacleNames[] = {
		"Zapertaya_dver",
		"Dver_s_kodovoy_panelyu",
		"Otravlyayushchiy_gaz",
		"Zatoplennaya_zona",
		"Zabitaya_dver",
		"Ventilyatsiya_ili_panel_na_vintakh",
		"Pozhar",
		"Slomannyy_lift",
		"Naeektrizovannaya_voda",
		"Orda_zombiy",
		"Turret",
		"Lazernaya_sistema_okhrany",
		"Otklyuchenie_pitaniya",
		"Goryashchiy_musor",
		"Kirpichnaya_stena"
	};

	std::vector<SOclass> solutions = {
		{ 0, UnlockKey },
		{ 1, UnlockCode },
		{ 2, CutMetal | Cut | Smash },
		{ 3, CutMetal | Cut },
		{ 4, CutMetal | Cut | Burn },
		{ 5, GasSafe },
		{ 6, Smash },
		{ 7, Cut | Smash },
		{ 8, Unscrew | Repair },
		{ 9, ValveControl | Extinguish },
		{ 10, Insulated | Float },
		{ 11, Extinguish },
		{ 12, PowerOn | Extinguish },
		{ 13, PowerOn | PowerOff },
		{ 14, Shoot }
	};

	std::vector<SOclass> obstacles = {
		{ 0, UnlockKey | CutMetal | Cut },
		{ 1, UnlockCode | CutMetal | Cut },
		{ 2, GasSafe | ValveControl | Smash },
		{ 3, ValveControl | Float },
		{ 4, Cut | Smash },
		{ 5, Unscrew | CutMetal | Cut },
		{ 6, Extinguish | ValveControl },
		{ 7, Repair | PowerOff },
		{ 8, Insulated | PowerOff },
		{ 9, Shoot | Hide | Cut | Smash | CutMetal | Meat },
		{ 10, Shoot | PowerOff | Cut | Smash },
		{ 11, Shoot | PowerOn | PowerOff },
		{ 12, PowerOn | PowerOff },
		{ 13, Extinguish },
		{ 14, Smash }
	};

	static std::mt19937 rng(
		std::chrono::steady_clock::now().time_since_epoch().count()
	);
	std::uniform_int_distribution<int> dist(6, 8);
	int sampleSize = dist(rng);
	std::vector<SOclass> solutionsToObstacle;
	solutionsToObstacle.reserve(sampleSize);
	std::vector<int> indices(solutions.size());
	std::iota(indices.begin(), indices.end(), 0);
	std::shuffle(indices.begin(), indices.end(), rng);

	int count = std::min( sampleSize, static_cast<int>(solutions.size()) );
	for (int k = 0; k < count; ++k) {
		int s = indices[k];
		uint32_t mask = 0;
		for (int o = 0; o < obstacles.size(); ++o) {
			if (solutions[s].mask & obstacles[o].mask) {
				mask |= 1 << o;
			}
		}
		solutionsToObstacle.push_back({ solutions[s].id, mask });
	}
	// constexpr int solsSize = sizeof(solutions) / sizeof(SOclass);
	// std::vector<int> sols;
	// sols.reserve(solsSize);
	// for(int i = 0; i < solsSize; i++) {
	// 	sols.push_back(solutions[i].mask);
	// }

	std::vector<int> solutionsGroupStarts = sortAndGroupSolutions(solutionsToObstacle);
	std::vector<int> obstaclesGroupStarts = sortAndGroupObstacles(obstacles, solutionsToObstacle, solutionsGroupStarts);
	int solutionsCount = solutionsToObstacle.size();
	int obstaclesCount = obstacles.size();
	float posx = 0;
	for (int g = 0; g < solutionsGroupStarts.size(); g++) {
		int start = solutionsGroupStarts[g];
		int end = (g + 1 < solutionsGroupStarts.size()) ? solutionsGroupStarts[g + 1] : solutionsToObstacle.size();
		

		Vector3 center = Vector3(posx, 2, -15);
		float roomWidth = 12.0f;
		float roomDepth = 8.0f;
		float wallHeight = 5.0f;
		float wallThickness = 0.4f;

		int solutionCount = end - start;
		int columns = std::min(4, solutionCount);
		float spacingX = roomWidth / (columns + 1);
		float spacingZ = 2.0f;

		for (int n = 0; n < solutionCount; ++n) {
			int i = start + n;
			float hue = float(i) / solutionsCount; 
			int col = n % columns;
			int row = n / columns;

			float x = -roomWidth * 0.5f + spacingX * (col + 1);
			float z = -roomDepth * 0.5f + 1.5f + row * spacingZ;

			Object sol = ECS::createObject();
			sol.transform.position = center + Vector3(-19 + x, 0, z);
			sol.AddComponent<Rigidbody>();
			sol.AddComponent<CubeCollider>();
			sol.AddComponent<Takeable>();
			sol.AddComponent<SolutionObstacle>().isObstacle = false;
			sol.GetComponent<SolutionObstacle>().mask = solutions[solutionsToObstacle[i].id].mask;
			sol.AddComponent<RenderView>().mesh_index = MESH_Cube;
			sol.GetComponent<RenderView>().materals[0] = MaterialManager::CreateMaterial(Material(SHADER_standartShader, TEX_White, 0, Color::HSV(hue, 1.0f, 1.0f)));

			Object solchild = ECS::createObject();
			solchild.transform.scale = 0.7f;
			solchild.transform.position = Vector3(0, 0, 0.6f);
			solchild.AddComponent<TextView>().text = solutionNames[solutionsToObstacle[i].id];
			solchild.GetComponent<TextView>().buildMesh();
			solchild.setParent(sol);
		}

		int start1 = obstaclesGroupStarts[g];
		int end1 = (g + 1 < obstaclesGroupStarts.size()) ? obstaclesGroupStarts[g + 1] : obstacles.size();
		// =====================================================
		// ЗАДНЯЯ СТЕНА
		// =====================================================
		{
			Object wall = ECS::createObject();
			wall.transform.position = center + Vector3(0, 0, -roomDepth * 0.5f);
			wall.transform.scale = Vector3(roomWidth, wallHeight, wallThickness);
			wall.AddComponent<CubeCollider>();
			wall.AddComponent<RenderView>().mesh_index = MESH_Cube;
			wall.GetComponent<RenderView>().materals[0] = 2;
		}


		// =====================================================
		// ЛЕВАЯ СТЕНА
		// =====================================================
		{
			Object wall = ECS::createObject();
			wall.transform.position = center + Vector3(-roomWidth * 0.5f, 0, 0);
			wall.transform.scale = Vector3(wallThickness, wallHeight, roomDepth);
			wall.AddComponent<CubeCollider>();
			wall.AddComponent<RenderView>().mesh_index = MESH_Cube;
			wall.GetComponent<RenderView>().materals[0] = 2;
		}


		// =====================================================
		// ПРАВАЯ СТЕНА
		// =====================================================

		{
			Object wall = ECS::createObject();
			wall.transform.position = center + Vector3(roomWidth * 0.5f, 0, 0);
			wall.transform.scale = Vector3(wallThickness, wallHeight, roomDepth);
			wall.AddComponent<CubeCollider>();
			wall.AddComponent<RenderView>().mesh_index = MESH_Cube;
			wall.GetComponent<RenderView>().materals[0] = 2;
		}

		int doorCount = end1 - start1;
		float doorWidth = roomWidth / doorCount;
		for (int i = start1; i < end1; i++) {
			float hue = float(i) / obstaclesCount;
			int doorIndex = i - start1;
			float doorX = -roomWidth * 0.5f + doorWidth * 0.5f + doorIndex * doorWidth;

			Object obs = ECS::createObject();
			obs.transform.position = center +  Vector3(doorX, 0, roomDepth * 0.5f);
			obs.transform.scale = Vector3(doorWidth, 5, 0.4f);
			obs.AddComponent<CubeCollider>();
			obs.AddComponent<SolutionObstacle>().isObstacle = true;
			obs.GetComponent<SolutionObstacle>().mask = obstacles[i].mask;
			obs.AddComponent<RenderView>().mesh_index = MESH_Cube;
			obs.GetComponent<RenderView>().materals[0] = MaterialManager::CreateMaterial(Material(SHADER_standartShader, TEX_White, 0, Color::HSV(hue, 1.0f, 1.0f)));

			Object obschild = ECS::createObject();
			float base = 0.5f;
			obschild.transform.scale = Vector3(base / obs.transform.scale.x, base / obs.transform.scale.y, base / obs.transform.scale.z);
			obschild.transform.position = Vector3(0, 0, 0.6f);
			obschild.AddComponent<TextView>().text = obstacleNames[obstacles[i].id];
			obschild.GetComponent<TextView>().buildMesh();
			obschild.setParent(obs);
		}
		posx += 18;
	}

	Object obschild = ECS::createObject();
	obschild.transform.position = Vector3(posx - 18, 2, -15);;
	obschild.AddComponent<TextView>().text = "LOSER";
	obschild.GetComponent<TextView>().buildMesh();


	// generatable.AddComponent<HouseGenerator>();
	// generatable.GetComponent<HouseGenerator>().GenerateHouse(layers[i]);
	Object generatable = ECS::createObject();
	generatable.transform.position = {0, 2, 0};
	generatable.transform.scale = 3;
	generatable.AddComponent<RenderView>().mesh_index = MESH_Cube;
	generatable.GetComponent<RenderView>().materals[0] = MaterialManager::CreateMaterial(Material(SHADER_textShader, TEX_Atlas, 0, 0xff));


	generatable = ECS::createObject();
	generatable.transform.position = {3, 2, 0};
	generatable.transform.scale = 3;
	generatable.AddComponent<RenderView>().mesh_index = MESH_Cube;
	generatable.GetComponent<RenderView>().materals[0] = MaterialManager::CreateMaterial(Material(SHADER_standartShader, TEX_Atlas, 0, 0xff));

	generatable = ECS::createObject();
	generatable.transform.position = {0, 5, 0};
	generatable.transform.scale = 3;
	generatable.AddComponent<RenderView>().mesh_index = MESH_Cube;
	generatable.GetComponent<RenderView>().materals[0] = MaterialManager::CreateMaterial(Material(SHADER_standartShader, 0, 0, 0xff));
}


void Scene::Start() {
	PrefabSystem::getInstance().createMaterials();
	createMainSimulation();
	ShardsManager::getInstance().init();
	printf("%d %d %d %d\n", sizeof(RenderView), sizeof(Object), sizeof(Component), sizeof(Transform));
	
	Object panel = ECS::createObject();
	panel.transform.scale = 2;
	panel.AddComponent<RenderView>().layout = 1;
	panel.AddComponent<Camera>().renderLayout = 1;
	panel.GetComponent<RenderView>().materals[0] = PrefabSystem::getInstance().mainMaterial;

	NavMeshSystem::getPtr()->Start();
}

void Scene::Update() {
	if(IOSystem::getWindowResizeFinished()) {
		Rect window = IOSystem::getWindow().getInnerSize();
		Rect renderSize = window * SettingsSystem::GetSettings().resolution;

		int width = renderSize.width();
		int height = renderSize.height();
		Span<Camera> cameras = ECS::GetComponents<Camera>();
		for(auto& cam : cameras) {
			TextureManager::ResizeFrameBuffer(cam.frameBufferIndex, width, height);
		}

		constexpr float REFERENCE_WIDTH  = 1920.0f;
		constexpr float REFERENCE_HEIGHT = 1080.0f;
		float uiScale = std::min(window.width() / REFERENCE_WIDTH, window.height() / REFERENCE_HEIGHT );
		Span<UILayout> uiLayouts = ECS::GetComponents<UILayout>();
		for(auto & layout: uiLayouts) {
			UISystem::getInstance().Rebuild(layout.object, window.width(), window.height(), uiScale);
		}
	}
	InputComponentUpdate();

	NavMeshSystem::getPtr()->Update();

	Span<CameraControlSystem> cameraControlSystems = ECS::GetComponents<CameraControlSystem>();
	for (int i = 0; i < cameraControlSystems.size(); i++) {
		cameraControlSystems[i].Update();
	}

	InventoryManager::getInstance().Update();
	UISystem::getInstance().Update();
}


void Scene::FixedUpdate() {
	PhysicSystem::getInstance()->calculatePhysic();

	Span<BotLogic> botLogics = ECS::GetComponents<BotLogic>();
	for (int i = 0; i < botLogics.size(); i++) {
		botLogics[i].Update();
	}

	ClientServerSystem::getInstance().FixedUpdate();

	Span<CameraControlSystem> cameraControlSystems = ECS::GetComponents<CameraControlSystem>();
	for (int i = 0; i < cameraControlSystems.size(); i++) {
		cameraControlSystems[i].FixedUpdate();
	}
}