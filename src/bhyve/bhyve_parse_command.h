/*
 * bhyve_parse_command.h: Bhyve command parser
 *
 * Copyright (C) 2016 Fabian Freyer
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Author: Fabian Freyer <fabian.freyer@physik.tu-berlin.de>
 */

#ifndef __BHYVE_PARSE_COMMAND_H__
# define __BHYVE_PARSE_COMMAND_H__

virDomainDefPtr bhyveParseCommandLineString(const char* nativeConfig,
                                            unsigned caps,
                                            virDomainXMLOptionPtr xmlopt);

#endif /* __BHYVE_PARSE_COMMAND_H__*/
