./clf1.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clf1.cpp:  level.read((char *)&t->type, 1);
./clf1.cpp:  level.read((char *)&t->feature, 1);
./clf1.cpp:  level.read((char *)&t->flags, 1);
./clf1.cpp:  level.read((char *)&t->placeholder, 1);
./clf1.cpp:  level.read((char *)&t->health, 2);
./clf1.cpp:  output->setgrid(t);
./clf1.cpp:  level.write((const char *)&t->type, sizeof(t->type));
./clf1.cpp:  count += sizeof(t->type);
./clf1.cpp:  level.write((const char *)&t->feature, sizeof(t->feature));
./clf1.cpp:  count += sizeof(t->feature);
./clf1.cpp:  level.write((const char *)&t->flags, sizeof(t->flags));
./clf1.cpp:  count += sizeof(t->flags);
./clf1.cpp:  level.write((const char *)&t->placeholder, sizeof(t->placeholder));
./clf1.cpp:  count += sizeof(t->placeholder);
./clf1.cpp:  level.write((const char *)&t->health, sizeof(t->health));
./clf1.cpp:  count += sizeof(t->health);
./clkinputman.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clkinputman.cpp:        t->trigger(e);
./clkinputman.cpp:  newtrigger->id = id;
./clkinputman.cpp:  newtrigger->id = id;
./clkinputman.cpp:    if (t->id == id) {
./clkkeybind.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clkkeybind.cpp:    itrigger->trigger(e);
./clkkeybind.cpp:  registration = manager->registerinput(SDL_KEYDOWN, new kbdbtrig(*this));
./clkkeybind.cpp:    manager->deregister(SDL_KEYDOWN, registration);
./clkmbuttonbind.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clkmbuttonbind.cpp:    t->mktype((tiletype)stype);
./clkmbuttonbind.cpp:    t->feature = (tilefeature)sfeat;
./clkmbuttonbind.cpp:    t->flags = sflag;
./clkmenutrig.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clkrand.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clkterminator.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clkterminator.cpp:  registration = manager->registerinput(SDL_QUIT, new quittrig(*this));
./clkterminator.cpp:  manager->deregister(SDL_QUIT, registration);
./clktex.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clktex.cpp:  SDL_Rect srcregion = {sheetoffset.x + (c - startchar) * sheetoffset.w,
./clktex.cpp:  SDL_Rect srcregion = {sheetoffset.x + (c - startchar) * sheetoffset.w,
./clkviewport.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clkwin.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./clkwin.cpp:      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
./clkwin.cpp:  SDL_SetRenderDrawColor(ren.get(), color->r, color->g, color->b, color->a);
./door.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./feature.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./grid.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./grid.cpp:    t->mktype((i % 7) ? tiletype::FLOOR : tiletype::WALL);
./grid.cpp:      moving.get()->tick();
./grid.cpp:    if (t->mon == nullptr) {
./grid.cpp:      if (t->feature.get() && t->feature.get()->sprite)
./grid.cpp:                      t->feature.get()->sprite);
./grid.cpp:            compbit(tile::ttypes[(int)t->type].flags, tileflag::PASSABLE)
./grid.cpp:      t->mon->draw();
./grid.cpp:  if (!dest->mon &&
./grid.cpp:      compbit(dest->flags(), tileflag::PASSABLE)) {
./grid.cpp:    gettile(m->getx(), m->gety())->mon = nullptr;
./grid.cpp:    dest->mon = m;
./grid.cpp:    m->setx(x);
./grid.cpp:    m->sety(y);
./grid.cpp:    if (dest->feature.get())
./grid.cpp:      dest->feature.get()->step(*m);
./grid.cpp:    return m->getcoords();
./grid.cpp:  m.get()->g = this;
./grid.cpp:  m.get()->x = 0;
./grid.cpp:  m.get()->y = 0;
./grid.cpp:    monsters.front().get()->managerreg(kman);
./grid.cpp:  m->g = this;
./grid.cpp:  m->x = 0;
./grid.cpp:  m->y = 0;
./grid.cpp:    monsters.front().get()->managerreg(kman);
./grid.cpp:    m.get()->managerreg(kman);
./grid.cpp:    m.get()->managerdereg();
./grid.cpp:    if ((gettile(i)->mon == nullptr) &&
./grid.cpp:        compbit(tile::ttypes[(int)gettile(i)->type].flags, tileflag::PASSABLE))
./grid.cpp:  m->g = this;
./grid.cpp:  int roll = clk::randctl::randint<int>(0, candidates.size() - 1);
./grid.cpp:  m->x = candidates[roll].second % w;
./grid.cpp:  m->y = candidates[roll].second / w;
./grid.cpp:    m->managerreg(kman);
./grid.cpp:  return {m->x, m->y};
./gridman.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./gridman.cpp:  clevel.get()->managerreg(&kman);
./gridman.cpp:  clevel.get()->managerdereg();
./gridman.cpp:    levels.front().get()->managerdereg(); // FIXME: Make the grid deregister
./gridman.cpp:    clevel.get()->managerreg(&kman);
./gridman.cpp:  clevel.get()->newmonst(protomonster::montype::human);
./main.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./main.cpp:const char *copyright = "Copyright (c) John Allen Whitley, 2022, BSD 3-Clause";
./main.cpp:    gman.clevel.get()->tick();
./main.cpp:    gman.clevel.get()->draw();
./main.cpp:        std::to_string(gman.clevel.get()->monsters.front().get()->meter));
./messaging.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./messaging.cpp:  for (int i = queue.size() - 1; i >= 0 && (queue.size() - i) < rows + 1; i--) {
./messaging.cpp:    font.drawstring(vports::MESSAGES, 0, (rows - (queue.size() - i)) * FONTHEI,
./monster.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./monster.cpp:monster::~monster() { g->gettile(x, y)->mon = nullptr; }
./monster.cpp:  meter -= speed;
./monster.cpp:  g->font.drawchar(vports::GRID, x * g->gettilew(), y * g->gettileh(), family);
./monster.cpp:int monster::hurt(int delta) { return hp -= delta; }
./monster.cpp:  if (g->blocking) {
./monster.cpp:    g->blocking = 0;
./monster.cpp:    return g->movemonster(this, newx, newy);
./monster.cpp:  if (g->blocking)
./monster.cpp:    if (g->gettile(x, y)->feature && g->gettile(x, y)->feature.get()->fflags) {
./monster.cpp:      g->gettile(x, y)->feature.get()->act(*this);
./monster.cpp:      g->blocking = 0;
./monster.cpp:    action = [this](int x, int y) { return this->move(x, y); };
./monster.cpp:    action = [this](int x, int y) { return this->act(x, y); };
./monster.cpp:    action(x - 1, y - 1);
./monster.cpp:    action(x, y - 1);
./monster.cpp:    action(x + 1, y - 1);
./monster.cpp:    action(x - 1, y);
./monster.cpp:    action(x - 1, y + 1);
./monster.cpp:    manager->registerinput((SDL_Keycode)i, new montrig(*this));
./monster.cpp:  manager->registerinput(SDLK_a, new montrig(*this));
./monster.cpp:  manager->registerinput(SDLK_ESCAPE, new montrig(*this));
./monster.cpp:    manager->deregister(i);
./protomonster.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./protomonster.cpp:    protomonster::aifuncs{{[](monster &m) { m.g->blocking = 1; }}};
./tile.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
./tileflag.cpp:// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
