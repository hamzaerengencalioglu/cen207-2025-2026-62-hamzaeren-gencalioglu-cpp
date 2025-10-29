#include "../header/file_utility.h"

int loadUsersFromBinaryFile(HashTable* ht, const char* filename)
{
	FILE* file = std::fopen(filename, "rb");
	if (!file) {
		// Dosya yoksa boş başlangıç; ID'yi 1'e çek
		currentID = 1;
		return 1; // başarı kabul ediliyor (boş durum)
	}

	User tempUser{};
	int maxID = 0;

	while (std::fread(&tempUser, sizeof(User), 1, file) == 1) {
		User* existingUser = nullptr;
		// Aynı kullanıcı yoksa tabloya ekle
		if (!findUserBrent(ht, tempUser.username, &existingUser) || existingUser == nullptr) {
			insertUserBrent(ht, tempUser.id, tempUser.username, tempUser.password);
		}
		if (tempUser.id > maxID) {
			maxID = tempUser.id;
		}
	}

	std::fclose(file);
	currentID = maxID + 1;
	return 1;
}

int saveUsersToBinaryFile(const HashTable* ht, const char* filename)
{
	FILE* file = std::fopen(filename, "wb");
	if (!file) {
		return 0;
	}

	for (int i = 0; i < TABLE_SIZE; ++i) {
		const User* user = ht->table[i];
		if (user) {
			std::fwrite(user, sizeof(User), 1, file);
		}
	}

	std::fclose(file);
	return 1;
}

int getNextID(const char* filename, size_t recordSize)
{
	FILE* file = std::fopen(filename, "rb");
	if (!file) {
		return 1; // dosya yoksa ilk ID 1
	}

	void* record = std::malloc(recordSize);
	if (!record) {
		std::perror("Memory allocation failed");
		std::fclose(file);
		return 1;
	}

	int maxID = 0;

	// Varsayım: her kaydın ilk alanı int ID
	while (std::fread(record, recordSize, 1, file) == 1) {
		int recID = *reinterpret_cast<int*>(record);
		if (recID > maxID) {
			maxID = recID;
		}
	}

	std::free(record);
	std::fclose(file);
	return maxID + 1;
}

char* getFormattedDate(int daysToAdd)
{
	char* dateStr = static_cast<char*>(std::malloc(11)); // YYYY-MM-DD + '\0'
	if (!dateStr) {
		std::perror("Memory allocation failed");
		std::exit(EXIT_FAILURE);
	}

	std::time_t now = std::time(nullptr);
	std::tm* ltm = std::localtime(&now);

	ltm->tm_mday += daysToAdd;
	std::mktime(ltm); // normalize

	std::snprintf(dateStr, 11, "%04d-%02d-%02d",
		1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
	return dateStr;
}
