#include <gtest/gtest.h>
#include "balans.h"

// Для тестирования AccountingEntry нужно создать мок для ввода
class TestAccountingEntry : public AccountingEntry {
public:
    TestAccountingEntry(const std::string& account, double debit, double credit) {
        // Обход конструктора с вводом
        accountName = account;
        this->debit = debit;
        this->credit = credit;
    }
};

TEST(AccountingEntryTest, Getters) {
    TestAccountingEntry entry("Счет 01", 1000.0, 500.0);
    
    EXPECT_EQ(entry.getDebit(), 1000.0);
    EXPECT_EQ(entry.getCredit(), 500.0);
}

TEST(AccountingEntryTest, BalanceCheck) {
    std::vector<TestAccountingEntry> journal = {
        TestAccountingEntry("Счет 01", 1000.0, 500.0),
        TestAccountingEntry("Счет 02", 500.0, 1000.0)
    };
    
    double totalDebit = 0, totalCredit = 0;
    for (const auto& entry : journal) {
        totalDebit += entry.getDebit();
        totalCredit += entry.getCredit();
    }
    
    EXPECT_EQ(totalDebit, 1500.0);
    EXPECT_EQ(totalCredit, 1500.0);
    EXPECT_EQ(totalDebit, totalCredit);  // Баланс сошелся
}