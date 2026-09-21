# Utility Bill Calculator (C++)

## Rate Structure
- **Base Fee**: $18.50 (Flat monthly fee)
- **Tier 1 (0 to 500 kWh)**: $0.08 per kWh
- **Tier 2 (501 to 1,000 kWh)**: $0.12 per kWh
- **Tier 3 (> 1,000 kWh)**: $0.16 per kWh
- **Clean Energy Tax**: 5.5% levied on consumption subtotal only

## Compilation & Running

```bash
g++ -std=c++11 -O2 src/main.cpp -o utility_calculator
./utility_calculator

Tests:## Test Cases Verification Matrix

| Test ID | Previous Reading | Current Reading | Net Units Used | Expected Tier Breakdown | Consumption Subtotal | Municipal Tax (5.5%) | Expected Total Due | Test Case Objective |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-01** | 1000.00 | 1000.00 | 0.00 | T1: $0.00<br>T2: $0.00<br>T3: $0.00 | $0.00 | $0.00 | $18.50 | Zero consumption boundary check; confirms base fee is billed alone. |
| **TC-02** | 500.00 | 850.00 | 350.00 | T1: $28.00<br>T2: $0.00<br>T3: $0.00 | $28.00 | $1.54 | $48.04 | Mid-Tier 1 boundary ($350 \times 0.08$). |
| **TC-03** | 1200.00 | 1950.00 | 750.00 | T1: $40.00<br>T2: $30.00<br>T3: $0.00 | $70.00 | $3.85 | $92.35 | Transition into Tier 2 ($500 \times 0.08 + 250 \times 0.12$). |
| **TC-04** | 2000.00 | 3500.00 | 1500.00 | T1: $40.00<br>T2: $60.00<br>T3: $80.00 | $180.00 | $9.90 | $208.40 | Multi-tier saturation spanning Tiers 1, 2, and 3. |
| **TC-05** | -50.00 $\rightarrow$ 1000.00 | 900.00 $\rightarrow$ 1100.00 | 100.00 | T1: $8.00<br>T2: $0.00<br>T3: $0.00 | $8.00 | $0.44 | $26.94 | Rejection of negative inputs and inverted readings followed by valid calculation. |
