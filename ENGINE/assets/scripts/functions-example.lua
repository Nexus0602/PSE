some_variable = 3^(5*2);

function factorial(n)
    if n==1 then
        return 1
    end
    return n*factorial(n-1)
end

print("The cube of number 3 is equal to " .. cube(3))