#pragma once
#include "Problem.h"
#include "Solution.h"
#include <fstream>
class JsonManager
{
public:

	// GET request
	static bool sendGetMatches() {
		/*const String jsonFoldername = DateTime::Now().format(U"yyyy-MM-dd HH-mm-ss");
		const String jsonsaveFolder = U"json/" + jsonFoldername + U"/";*/

		const String token = U"gifu9c7ad1365ffacfb468599408e9733fb1440ae3b7ab38c8094b9d19f5eccd";
		const URL url = U"localhost:8080/problem";
		const HashTable<String, String> headers = { {U"Procon-Token", token} };
		const FilePath saveFilePath = U"get_matches_response.json";

		//if GET request OK
		if (const auto response = SimpleHTTP::Get(url, headers, saveFilePath)) {
			Print << response.getStatusLine();
			Logger << response.getStatusLine();

			if (response.isOK()) {
				const JSON json = JSON::Load(saveFilePath);
				if (not json) {
					throw Error{ U"Failed to load " + saveFilePath };
				}
			}
			else {
				return false;
			}
		}
		else { // if Get request failed
			Print << U"Failed to send getMatches.";
			Logger << U"Failed to send getMatches.";
			return false;
		}

		return true;
	}


	// POST request
	static bool sendPostAction() {

		const URL url = U"localhost:8080/answer";
		const String token = U"gifu9c7ad1365ffacfb468599408e9733fb1440ae3b7ab38c8094b9d19f5eccd";
		const HashTable<String, String> headers = { {U"Procon-Token", token}, {U"Content-Type", U"application/json"} };
		const FilePath saveFilePath = U"post_action_response.json";

		//preparation for json to send
		JSON sendjson = JSON::Load(U"solution.json");
		const std::string data = sendjson.formatUTF8();

		//post request to server
		if (auto response = SimpleHTTP::Post(url, headers, data.data(), data.size(), saveFilePath)) {
			Print << response.getStatusLine();
			Logger << response.getStatusLine();

			if (response.isOK()) {
				const JSON json = JSON::Load(saveFilePath);
				if (not json) {
					throw Error{ U"Failed to load " + saveFilePath };
					return false;
				}
				else {
					long long rev = json[U"revision"].get<long long>();
					Print << U"rev: " << rev;
					Logger << U"rev: " << rev;
					return true;
				}
			}
			else {
				return false;
			}
		}
		else {
			Print << U"Failed to post actions.";
			Logger << U"Failed to post actions.";
			return false;
		}

	}

	// JSON parse
	static std::optional<Problem> jsonParse() {
		Problem problem;

		FilePath jsonFilePath = U"get_matches_response.json";
		JSON json = JSON::Load(jsonFilePath);

		if (!json)
		{
			// JSONファイルの読み込みに失敗した場合
			Console << U"Failed to load JSON file.";
			//return std::nullopt;
			return std::nullopt;
		}
		else {
			int boardWidth = json[U"board"][U"width"].get<int>();
			int boardHeight = json[U"board"][U"height"].get<int>();
			problem.board.width = boardWidth;
			problem.board.height = boardHeight;
			//Print << U"Width: " << problem.b.width << U" Height: " << boardHeight;
			Array<String> start(boardHeight);
			Array<String> goal(boardHeight);
			
			for (int i = 0; i < boardHeight; i++) {
				start[i] = json[U"board"][U"start"][i].get<String>();
			}
			
			for (int i = 0; i < boardHeight; i++) {
				goal[i] = json[U"board"][U"goal"][i].get<String>();
			}
			problem.board.start = start;
			problem.board.goal = goal;
			//Print << U"Start board";
			/*for (int i = 0; i < boardHeight; i++) {
				Print << problem.b.start[i];
			}*/
			//Print << U"Goal board";
			/*for (int i = 0; i < boardHeight; i++) {
				Print << problem.b.goal[i];
			}*/
			int n = json[U"general"][U"n"].get<int>();
			problem.general.n = n;
			//Print << U"general patterns: " << n;
			Array<GeneralPattern> patterns;
			for (int i = 0; i < n; i++) {
				//Print << U"Pattern " << i+1 << U":";
				int h = json[U"general"][U"patterns"][i][U"height"].get<int>();
				int p = json[U"general"][U"patterns"][i][U"p"].get<int>();
				int w = json[U"general"][U"patterns"][i][U"width"].get<int>();
				
				patterns.emplace_back(p, w, h);
				/*Print << U"num: " << patterns[i].p;
				Print << U"width:" << patterns[i].width;
				Print << U"height: " << patterns[i].height;*/

				//Print << U"cells: ";
				for (int j = 0; j < h; j++) {
					patterns[i].cells[j] = json[U"general"][U"patterns"][i][U"cells"][j].get<String>();
					//Print << patterns[i].cells[j];
				}
			}

			problem.general.patterns = patterns;
			

			return problem;
		}
	}

	static bool jsonWrite(Solution solution) {
		JSON json;

		json[U"n"] = solution.n;
		for (int i = 0; i < solution.n; i++) {
			json[U"ops"][i][U"p"] = solution.ops[i].p;
			json[U"ops"][i][U"x"] = solution.ops[i].x;
			json[U"ops"][i][U"y"] = solution.ops[i].y;
			json[U"ops"][i][U"s"] = solution.ops[i].s;
		}
		//json.save(U"solution.json");
		TextWriter writer(U"solution.json", TextEncoding::UTF8_NO_BOM);
		if (writer.isOpen())
		{
			writer.write(Unicode::FromUTF8(json.formatUTF8())); // JSONをフォーマットして書き出し
			return true;
		}
		else
		{
			return false;
		}

		// delete first 3 byte
		/*std::string outputFileName = "solution_rev.json";
		std::ifstream inputFile("solution.json", std::ios::binary);
		if (!inputFile) {
			Print << U"json write failed (1)";
			return false;
		}

		inputFile.seekg(3);

		std::vector<char> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
		inputFile.close();

		std::ofstream outputFile(outputFileName, std::ios::binary);
		if (!outputFile) {
			Print << U"json write failed (2)";
			return false;
		}

		outputFile.write(buffer.data(), buffer.size());
		outputFile.close();*/

		return true;
	}


	static void sendActions(Solution result) {
		// write json file & POST request
		if (JsonManager::jsonWrite(result)) {
			Print << U"Json file write OK";
			Logger << U"Json file write OK";


			if (JsonManager::sendPostAction()) {
				Print << U"Post Action OK";
				Logger << U"Post Action OK";
			}
			else {
				Print << U"Post Action failed";
				Logger << U"Post Action failed";
			}
		}
		else {
			Print << U"Cannot write json file";
			Logger << U"Cannot write json file";
		}
	}
	
};

