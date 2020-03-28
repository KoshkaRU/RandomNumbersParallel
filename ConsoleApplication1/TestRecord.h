#pragma once

#include <string>

struct test_record {
	int value;
	std::string name;

	bool operator==(const test_record& second) const {

		const bool result = this->name == second.name && this->value == second.value;

			return result;
	}

};

namespace std {

	template<> struct hash<test_record> {

		using argument_type = test_record;
		using result_type = size_t;

		size_t operator()(const test_record& r) const {

			const std::hash<std::string> str_hash_fn;
			const std::hash<int> int_hash_fn;
			
			const size_t result = str_hash_fn(r.name) ^ int_hash_fn(r.value);

			return result;
		}

	};
};
