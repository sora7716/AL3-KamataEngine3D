#include "ContactRecord.h"
#include "algorithm"
void ContactRecord::AddRecord(int32_t number) {

	// 履歴に登録
	history_.push_back(number);
}

bool ContactRecord::CheckRecord(int32_t number) {

	bool record =  std::any_of(history_.begin(), history_.end(), [number](int32_t record) {
		return record == number;
	});

	return record;
}

void ContactRecord::Clear() {
	// 履歴を抹消
	history_.clear();
}