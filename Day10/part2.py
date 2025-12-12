import sys
import ast
from functools import reduce
from pulp import LpProblem, LpVariable, LpMinimize, lpSum, LpInteger, PULP_CBC_CMD


ans = 0
for indxLine, line in enumerate(sys.stdin):
    line = line.replace('{','[').replace('}',']')
    line = line.replace('(','[').replace(')',']')

    components = line.split(' ')
    components = components[1::]
    totals = ast.literal_eval(components[-1])
    buttons = tuple(ast.literal_eval(button) for button in components[:-1])
    
    n = len(totals)
    problem = LpProblem(f"Minimize_Machine_{indxLine}", LpMinimize)
    vars = [LpVariable(f"p{i}", lowBound=0, cat=LpInteger) for i in range(len(buttons))]
    problem += lpSum(vars[i] for i in range(len(buttons))), "Objective_Function"

    # add constraints
    for num in range(n):
        active_vars = []
        for indx, button in enumerate(buttons):
            if num in set(button):
                active_vars.append(vars[indx])
        problem += lpSum(active_vars) == totals[num], f"Constraing_{num}"
    
    problem.solve(PULP_CBC_CMD(msg=False))
    ans += int(problem.objective.value())
print(ans)