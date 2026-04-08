CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14 -MMD

UNIT_TESTS = pe-vector-tests
OBJS - main.o
DEPS = main.d

$(UNIT_TESTS): $(OBJS)
	$(CXX) -o $@ $^

clean:
	-@$(RM) $(UINT_TESTS)
	-$(DEPS)
	@$(RM) $(OBJS)

-include main.d
